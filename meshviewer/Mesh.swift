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
      mesh_create_geosphere(self.cpp_mesh_pointer, 1.0,  0)
    }
  
    func create_box()
    {
      mesh_create_box(self.cpp_mesh_pointer)
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
  
    func geometry() -> SCNGeometry
    {
      mesh_print_vertex_positions(self.cpp_mesh_pointer)
      let rawPtr = UnsafeRawPointer( mesh_vertex_position_data(self.cpp_mesh_pointer));
      let posData = NSData(bytes: rawPtr, length: MemoryLayout<Float32>.size * vertexCount * 3)
      let D = posData as Data
      let sourceVertices = SCNGeometrySource(data: D, semantic: SCNGeometrySource.Semantic.vertex, vectorCount: vertexCount, usesFloatComponents: true, componentsPerVector: 3, bytesPerComponent: MemoryLayout<Float32>.size, dataOffset: 0, dataStride: 3*MemoryLayout<Float32>.size)
      print(sourceVertices)
      

      let indices = Array<Int>(0..<vertexCount)
      let element = SCNGeometryElement(indices: indices, primitiveType: .line)

      let meshGeom =  SCNGeometry(sources: [sourceVertices], elements: [element])
      return meshGeom;
    }
  
  
  
}

