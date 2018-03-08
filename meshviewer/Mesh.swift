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
      mesh_create_geosphere(self.cpp_mesh_pointer, 1.0,  2)
    }
    
  
   /* public var vertexCount: Int {
        return Int(mesh_num_vertices(self.cpp_mesh_pointer))
    }
  
    public var name: String {
        return String(cString:mesh_name(self.cpp_mesh_pointer))
    }
  
    func load(_ filename:String) -> Bool {
      return Bool(mesh_load(self.cpp_mesh_pointer, filename.cCharArray))
    }
  
    func geometry(_ filename:String) -> SCNGeometry
    {
      let indices: [Int32] = [0, 1, 2, 3]
      
      let count = mesh_position_count(self.cpp_mesh_pointer);
     
      let rawPtr = UnsafeRawPointer( mesh_position_data(self.cpp_mesh_pointer));
      let posData = NSData(bytes: rawPtr, length: MemoryLayout<Float32>.size * count*3)
      
      let source = SCNGeometrySource(data: posData as Data, semantic: SCNGeometrySource.Semantic.vertex, vectorCount: count, usesFloatComponents: true, componentsPerVector: 3, bytesPerComponent: MemoryLayout<Float>.size, dataOffset: 0, dataStride: 0)
      let element = SCNGeometryElement(indices: indices, primitiveType: .triangleStrip)

      let meshGeom =  SCNGeometry(sources: [source], elements: [element])
      return meshGeom;
    }
  */
  
  
}

