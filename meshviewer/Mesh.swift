import Foundation
import SceneKit

public extension String {
    var cCharArray: UnsafeMutablePointer<Int8> {
        return UnsafeMutablePointer<Int8>(mutating: (self as NSString).utf8String!)
    }
}

public extension NSColor {
     var hexUInt32: UInt32 {
        let red = UInt32(self.redComponent * 0xFF)
        let green = UInt32(self.greenComponent * 0xFF)
        let blue = UInt32(self.blueComponent * 0xFF)
        let alpha = UInt32(self.alphaComponent * 0xFF)
        return (alpha << 24) + (red << 16) + (green << 8) + blue
    }
}

enum MeshPrimitives {
    case geoSphere
    case sphere
    case box
    case torus
    case tetrahedron
}

class Mesh: NSObject
{
    private let cpp_mesh_pointer: UnsafeMutableRawPointer
  
    var meshNode = Mesh.createNode()
  
    var useFaceNormals = true
  
    var isWireFrame = false
  
    func update()
    {
      if isWireFrame
        {
         self.meshNode.geometry = self.edgeGeometry()
         
        }
        else{
          self.meshNode.geometry = self.triangleGeometry(withFaceNormals:useFaceNormals)
        }
    }
  
    override init () {
        self.cpp_mesh_pointer = mesh_init()
        super.init()
    }
  
    deinit {
        mesh_deinit(self.cpp_mesh_pointer)
    }
  
    private static func createNode() -> SCNNode{
     return SCNNode()
    }
  
    func loadMesh(url: String, progressIndicator: NSProgressIndicator?){
  //  statusText.stringValue = "Status: Loading mesh \(url)"
    progressIndicator?.isHidden = false
    progressIndicator?.usesThreadedAnimation = true
    progressIndicator?.startAnimation(self)
    
   DispatchQueue.global(qos: .background).async {
      mesh_load(self.cpp_mesh_pointer, url.cCharArray)
      self.auto_center_and_scale()
      self.triangulate()
      self.colorize_faces()
    
    
      DispatchQueue.main.async{
        
          self.update()
          progressIndicator?.stopAnimation(self)
          progressIndicator?.isHidden = true
         // self.statusText.stringValue = "Status: idle"
      }
    }
    
  }
  
  /*
      if isWireFrame
    {
     
      meshNode?.geometry = mesh?.edgeGeometry()
      meshNode?.geometry?.firstMaterial?.lightingModel = SCNMaterial.LightingModel.constant
      meshNode?.geometry?.firstMaterial?.diffuse.contents  = #colorLiteral(red: 0.8446564078, green: 0.5145705342, blue: 1, alpha: 1)
    }
    else
    {
      meshNode?.geometry?.firstMaterial?.lightingModel = SCNMaterial.LightingModel.blinn
      meshNode?.geometry = mesh?.triangleGeometry(withFaceNormals:true)
    }
    */
  
    static func create_geo_sphere(radius : Float, numLevels : Int) -> Mesh
    {
      let mesh = Mesh();
      mesh_create_geosphere(mesh.cpp_mesh_pointer, radius,  numLevels)
      return mesh;
    }
  
    static func load(filename:String) -> Mesh
    {
      let mesh = Mesh();
     
      return mesh;
    }
  
    static func create_box()-> Mesh
    {
      let mesh = Mesh();
      mesh_create_box(mesh.cpp_mesh_pointer)
      return mesh;
    }
  
    static func create_torus(radius1 : Float, radius2 : Float)-> Mesh
    {
      let mesh = Mesh();
      mesh_create_torus(mesh.cpp_mesh_pointer, radius1, radius2, 10, 20)
      return mesh;
    }
  
    static func create_tetrahedron()-> Mesh
    {
      let mesh = Mesh();
      mesh_create_tetrahedron(mesh.cpp_mesh_pointer)
      return mesh;
    }
  
  
    func triangulate()
    {
      mesh_triangulate(self.cpp_mesh_pointer)
    }
  
    func colorize_faces(_ color : NSColor = #colorLiteral(red: 0.9607843161, green: 0.7058823705, blue: 0.200000003, alpha: 1))
    {
      colorize_mesh_faces(self.cpp_mesh_pointer,color.hexUInt32)
    }
  
    func auto_center_and_scale()
    {
      mesh_auto_center_and_scale(self.cpp_mesh_pointer);
    }
    
  
    public var vertexCount: Int {
        return Int(mesh_num_vertices(self.cpp_mesh_pointer))
    }
  
    public var edgeCount: Int {
        return Int(mesh_num_edges(self.cpp_mesh_pointer))
    }
  
    public var halfedgeCount: Int {
        return Int(mesh_num_halfedges(self.cpp_mesh_pointer))
    }
  
    public var faceCount: Int {
        return Int(mesh_num_faces(self.cpp_mesh_pointer))
    }
  
    public var triangleCount: Int {
        return Int(mesh_num_triangles(self.cpp_mesh_pointer))
    }
  
  
    func edgeGeometry() -> SCNGeometry
    {
      let positionPtr = UnsafeMutableRawPointer(mesh_halfedge_position_data_init(self.cpp_mesh_pointer))
      let positionData = Data(bytes: positionPtr!, count: MemoryLayout<Float32>.size * halfedgeCount * 3)
      mesh_halfedge_position_data_deinit(positionPtr!)
      
      let normalPtr = UnsafeMutableRawPointer(mesh_halfedge_normal_data_init(self.cpp_mesh_pointer))!
      let normalData = Data(bytes: normalPtr, count: MemoryLayout<Float32>.size * halfedgeCount * 3)
      mesh_halfedge_normal_data_deinit(normalPtr)
      
      
      let indexPtr = UnsafeMutableRawPointer(mesh_edge_halfedge_indices_init(self.cpp_mesh_pointer))!
      let indexData = Data(bytes: indexPtr, count: MemoryLayout<Int32>.size * edgeCount * 2)
      mesh_edge_halfedge_indices_deinit(indexPtr)
      
      let sourcePositions = SCNGeometrySource(data: positionData, semantic: SCNGeometrySource.Semantic.vertex, vectorCount: halfedgeCount, usesFloatComponents: true, componentsPerVector: 3, bytesPerComponent: MemoryLayout<Float32>.size, dataOffset: 0, dataStride: 3*MemoryLayout<Float32>.size)
      
      let sourceNormals = SCNGeometrySource(data: normalData, semantic: SCNGeometrySource.Semantic.normal, vectorCount: halfedgeCount, usesFloatComponents: true, componentsPerVector: 3, bytesPerComponent: MemoryLayout<Float32>.size, dataOffset: 0, dataStride: 3*MemoryLayout<Float32>.size)
      
      
      let element = SCNGeometryElement(data: indexData, primitiveType: .line, primitiveCount: edgeCount, bytesPerIndex: MemoryLayout<Int32>.size)
   
      let meshGeom =  SCNGeometry(sources: [sourcePositions, sourceNormals], elements: [element])
      
      return meshGeom;
    }
  
  
    func triangleGeometry(withFaceNormals: Bool) -> SCNGeometry
    {
      let positionPtr = UnsafeMutableRawPointer(mesh_halfedge_position_data_init(self.cpp_mesh_pointer))
      let positionData = Data(bytes: positionPtr!, count: MemoryLayout<Float32>.size * halfedgeCount * 3)
      mesh_halfedge_position_data_deinit(positionPtr!)
      
      let normalPtr : UnsafeMutableRawPointer
      if withFaceNormals
      {
        normalPtr = UnsafeMutableRawPointer(mesh_halfedge_face_normal_data_init(self.cpp_mesh_pointer))!
      }
      else
      {
         normalPtr = UnsafeMutableRawPointer(mesh_halfedge_normal_data_init(self.cpp_mesh_pointer))!
      }
      let normalData = Data(bytes: normalPtr, count: MemoryLayout<Float32>.size * halfedgeCount * 3)
      mesh_halfedge_normal_data_deinit(normalPtr)
      
      let colorPtr = UnsafeMutableRawPointer(mesh_halfedge_face_color_data_init(self.cpp_mesh_pointer))
      let colorData = Data(bytes: colorPtr!, count: MemoryLayout<Float32>.size * halfedgeCount * 4)
      mesh_halfedge_face_color_data_deinit(colorPtr!)
      
      let indexPtr = UnsafeMutableRawPointer(mesh_triangle_halfedge_indices_init(self.cpp_mesh_pointer))!
      let indexData = Data(bytes: indexPtr, count: MemoryLayout<Int32>.size * faceCount * 3)
      mesh_triangle_halfedge_indices_deinit(indexPtr)
      
      let sourcePositions = SCNGeometrySource(data: positionData, semantic: SCNGeometrySource.Semantic.vertex, vectorCount: halfedgeCount, usesFloatComponents: true, componentsPerVector: 3, bytesPerComponent: MemoryLayout<Float32>.size, dataOffset: 0, dataStride: 3 * MemoryLayout<Float32>.size)
      
      let sourceNormals = SCNGeometrySource(data: normalData, semantic: SCNGeometrySource.Semantic.normal, vectorCount: halfedgeCount, usesFloatComponents: true, componentsPerVector: 3, bytesPerComponent: MemoryLayout<Float32>.size, dataOffset: 0, dataStride: 3 * MemoryLayout<Float32>.size)
      
      let sourceColors = SCNGeometrySource(data: colorData, semantic: SCNGeometrySource.Semantic.color, vectorCount: halfedgeCount, usesFloatComponents: true, componentsPerVector: 4, bytesPerComponent: MemoryLayout<Float32>.size, dataOffset: 0, dataStride: 4 * MemoryLayout<Float32>.size)
     
      let element = SCNGeometryElement(data: indexData, primitiveType: .triangles, primitiveCount: faceCount, bytesPerIndex: MemoryLayout<Int32>.size)
      
      let meshGeom =  SCNGeometry(sources: [sourcePositions,sourceNormals, sourceColors], elements: [element])
      
      return meshGeom;
    }
  
  
  
}

