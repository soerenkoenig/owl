import Foundation
import SceneKit

public extension String {
    var cCharArray: UnsafeMutablePointer<Int8> {
        return UnsafeMutablePointer<Int8>(mutating: (self as NSString).utf8String!)
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
  
    override init () {
        self.cpp_mesh_pointer = mesh_init()
        super.init()
    }
    
    deinit {
        mesh_deinit(self.cpp_mesh_pointer)
    }
  
    func create_geo_sphere()
    {
      mesh_create_geosphere(self.cpp_mesh_pointer, 10.0,  3)
    }
  
    func create_box()
    {
      mesh_create_box(self.cpp_mesh_pointer)
    }
  
    func triangulate()
    {
      mesh_triangulate(self.cpp_mesh_pointer)
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
  
     public var quadCount: Int {
        return Int(mesh_num_quads(self.cpp_mesh_pointer))
    }
  /*
    public var name: String {
        return String(cString:mesh_name(self.cpp_mesh_pointer))
    }
  
    func load(_ filename:String) -> Bool {
      return Bool(mesh_load(self.cpp_mesh_pointer, filename.cCharArray))
    }*/
  
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
  
  
    func triangleGeometry() -> SCNGeometry
    {
      mesh_print_vertex_positions(self.cpp_mesh_pointer)
    
      let positionPtr = UnsafeMutableRawPointer(mesh_halfedge_position_data_init(self.cpp_mesh_pointer))
      let positionData = Data(bytes: positionPtr!, count: MemoryLayout<Float32>.size * halfedgeCount * 3)
      mesh_halfedge_position_data_deinit(positionPtr!)
      
      let normalPtr = UnsafeMutableRawPointer(mesh_halfedge_normal_data_init(self.cpp_mesh_pointer))!
      let normalData = Data(bytes: normalPtr, count: MemoryLayout<Float32>.size * halfedgeCount * 3)
      mesh_halfedge_normal_data_deinit(normalPtr)
      
      let indexPtr = UnsafeMutableRawPointer(mesh_triangle_halfedge_indices_init(self.cpp_mesh_pointer))!
      let indexData = Data(bytes: indexPtr, count: MemoryLayout<Int32>.size * faceCount * 3)
      mesh_triangle_halfedge_indices_deinit(indexPtr)
      
      let sourcePositions = SCNGeometrySource(data: positionData, semantic: SCNGeometrySource.Semantic.vertex, vectorCount: halfedgeCount, usesFloatComponents: true, componentsPerVector: 3, bytesPerComponent: MemoryLayout<Float32>.size, dataOffset: 0, dataStride: 3*MemoryLayout<Float32>.size)
      
      let sourceNormals = SCNGeometrySource(data: normalData, semantic: SCNGeometrySource.Semantic.normal, vectorCount: halfedgeCount, usesFloatComponents: true, componentsPerVector: 3, bytesPerComponent: MemoryLayout<Float32>.size, dataOffset: 0, dataStride: 3*MemoryLayout<Float32>.size)
     
      
  
      let element = SCNGeometryElement(data: indexData, primitiveType: .triangles, primitiveCount: faceCount, bytesPerIndex: MemoryLayout<Int32>.size)
   
      let meshGeom =  SCNGeometry(sources: [sourcePositions,sourceNormals], elements: [element])
      
      return meshGeom;
    }
  
  
  
}

