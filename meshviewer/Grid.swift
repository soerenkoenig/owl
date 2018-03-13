import Foundation
import SceneKit


class Grid : NSObject
{
  
  
  
  
    func geometry() -> SCNGeometry
    {
      let pos:[Float32] = [0,0,0, 10,0,0, 0,0,10, -10,0,0, 0,0,-10]
      let tex:[Float32] = [0.5,0.5,  1.0,0.5, 0.5,0.0, 0.0,0.5, 0.5,1.0]
      let normals = [SCNVector3(0,1,0), SCNVector3(0,1,0), SCNVector3(0,1,0), SCNVector3(0,1,0), SCNVector3(0,1,0)]
      let posData = Data(bytes: pos, count: MemoryLayout<Float32>.size*4 * pos.count)
      let texcoordData = Data(bytes: tex, count: MemoryLayout<Float32>.size*2 * tex.count)
      

     
    //  let n = MemoryLayout<SCNVector4>.size * pos.count
      //let posData = NSData(bytes: pointer, length: n)
      
      let sourcePositions = SCNGeometrySource(data: posData, semantic: SCNGeometrySource.Semantic.vertex, vectorCount: 5, usesFloatComponents: true, componentsPerVector: 3, bytesPerComponent: MemoryLayout<Float32>.size, dataOffset: 0, dataStride: MemoryLayout<Float32>.size*3)
      
     // let sourcePositions = SCNGeometrySource(vertices: pos)
      let sourceNormals = SCNGeometrySource(normals: normals)
      
       let sourceTexCoords = SCNGeometrySource(data: texcoordData, semantic: SCNGeometrySource.Semantic.texcoord, vectorCount: 5, usesFloatComponents: true, componentsPerVector: 2, bytesPerComponent: MemoryLayout<Float32>.size, dataOffset: 0, dataStride: MemoryLayout<Float32>.size*2)
      
      let ind:[Int32] = [0,2,1,0,3,2,0,4,3,0,1,4]
     // let ind:[Int32] = [0,2,1]
      
      let element = SCNGeometryElement(indices : ind, primitiveType: .triangles)
   
      let meshGeom =  SCNGeometry(sources: [sourcePositions,sourceTexCoords, sourceNormals], elements: [element])
      meshGeom.firstMaterial?.emission.contents = NSImage.Name("checker")
      meshGeom.firstMaterial?.emission.wrapS = .clampToBorder
      meshGeom.firstMaterial?.emission.wrapT = .clampToBorder
      
      return meshGeom;
    }
  
  
  
}


