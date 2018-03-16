import Foundation
import SceneKit


class Grid : NSObject
{
  
    func node() ->SCNNode
    {
    
      let gridNode = SCNNode();
      
      let textX = SCNText(string: "x", extrusionDepth: 0.0)
      
      let textXNode = SCNNode(geometry: textX)
      textXNode.scale = SCNVector3(0.02,0.02,0.02)
      textXNode.position = SCNVector3(10,0,0)
      textXNode.eulerAngles.x = -3.1415972/2;
      gridNode.addChildNode(textXNode)
   
      let textZ = SCNText(string: "z", extrusionDepth: 0.0)
      let textZNode = SCNNode(geometry: textZ)
      textZNode.scale = SCNVector3(0.02,0.02,0.02)
      textZNode.position = SCNVector3(0,0,10)
      textZNode.eulerAngles.x = -3.1415972/2;
      gridNode.addChildNode(textZNode)
     
      let floorNode = SCNNode(geometry: geometry())
    
      gridNode.addChildNode(floorNode)
      return gridNode;
    }
  
    func geometry() -> SCNGeometry
    {
      let pos:[Float32] = [-10,0,-10, 10,0,-10, 10,0,10, -10,0,10]
      let tex:[Float32] = [0.0,0.0,  1.0,0.0, 1.0,1.0, 0.0,1.0]
      let normals = [SCNVector3(0,1,0), SCNVector3(0,1,0), SCNVector3(0,1,0), SCNVector3(0,1,0)]
      let posData = Data(bytes: pos, count: MemoryLayout<Float32>.size*4 * pos.count)
      let texcoordData = Data(bytes: tex, count: MemoryLayout<Float32>.size*2 * tex.count)
      
      
      let sourcePositions = SCNGeometrySource(data: posData, semantic: SCNGeometrySource.Semantic.vertex, vectorCount: 4, usesFloatComponents: true, componentsPerVector: 3, bytesPerComponent: MemoryLayout<Float32>.size, dataOffset: 0, dataStride: MemoryLayout<Float32>.size*3)
      
      let sourceNormals = SCNGeometrySource(normals: normals)
      
      let sourceTexCoords = SCNGeometrySource(data: texcoordData, semantic: SCNGeometrySource.Semantic.texcoord, vectorCount: 5, usesFloatComponents: true, componentsPerVector: 2, bytesPerComponent: MemoryLayout<Float32>.size, dataOffset: 0, dataStride: MemoryLayout<Float32>.size*2)
      
      let ind:[Int32] = [0,2,1,0,3,2]
      
      let element = SCNGeometryElement(indices : ind, primitiveType: .triangles)
   
      let meshGeom =  SCNGeometry(sources: [sourcePositions,sourceTexCoords, sourceNormals], elements: [element])
     // meshGeom.firstMaterial?.diffuse.contents = NSImage.Name("checker")
      meshGeom.firstMaterial?.transparent.contents = Image.createGrid(21,21,49).image()
      meshGeom.firstMaterial?.transparent.mipFilter = .linear
      meshGeom.firstMaterial?.transparencyMode = .rgbZero
      meshGeom.firstMaterial?.transparency = 1
      meshGeom.firstMaterial?.emission.contents = Image.createGridColor(21,21,49).image()
      meshGeom.firstMaterial?.emission.mipFilter = .nearest
      meshGeom.firstMaterial?.diffuse.contents = Image.createGridColor(21,21,49).image()
      meshGeom.firstMaterial?.diffuse.mipFilter = .nearest
      meshGeom.firstMaterial?.isDoubleSided = true
      meshGeom.firstMaterial?.lightingModel = SCNMaterial.LightingModel.constant
     
      return meshGeom;
    }
  
  
  
}


