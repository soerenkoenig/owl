import Foundation
import SceneKit


class Grid : NSObject
{

    var coordinateAxisNode = Grid.createCoordinateAxis()
    var gridNode = Grid.createGridNode()
  
    var gridVisible: Bool = true
    {
      didSet{
        gridNode.opacity = gridVisible ? 1 : 0
      }
    }
  
    var coordinateAxisVisible: Bool = true
    {
      didSet{
        coordinateAxisNode.opacity = coordinateAxisVisible ? 1 : 0
      }
    }


    private static func arrow(_ color : CGColor) -> SCNNode
    {
      let arrowNode = SCNNode()
      let cylinderGeom = SCNCylinder(radius: 0.1, height: 4.0)
      let cylinderNode = SCNNode(geometry: cylinderGeom)
      cylinderNode.position = SCNVector3(0,cylinderGeom.height/2,0)
      cylinderGeom.firstMaterial?.diffuse.contents = color
      arrowNode.addChildNode(cylinderNode)
      
      let coneGeom = SCNCone(topRadius: 0, bottomRadius: 0.2, height: 0.8)
      let coneNode = SCNNode(geometry: coneGeom)
      coneNode.position = SCNVector3(0,cylinderGeom.height + coneGeom.height/2,0)
      coneGeom.firstMaterial?.diffuse.contents = color
      arrowNode.addChildNode(coneNode)
    
      return arrowNode
    }
  
    private static func createCoordinateAxis() -> SCNNode
    {
      let coordinateAxisNode = SCNNode()
      
      let arrowXNode = arrow(#colorLiteral(red: 0.7450980544, green: 0.1568627506, blue: 0.07450980693, alpha: 1))
      arrowXNode.eulerAngles.z = -CGFloat.pi/2
      coordinateAxisNode.addChildNode(arrowXNode)
      
      let arrowYNode = arrow(#colorLiteral(red: 0.2745098174, green: 0.4862745106, blue: 0.1411764771, alpha: 1))
      coordinateAxisNode.addChildNode(arrowYNode)
  
      let arrowZNode = arrow(#colorLiteral(red: 0.1411764771, green: 0.3960784376, blue: 0.5647059083, alpha: 1))
      arrowZNode.eulerAngles.x = CGFloat.pi/2
      coordinateAxisNode.addChildNode(arrowZNode)
     
      let sphereGeom = SCNSphere(radius: 0.1)
      sphereGeom.firstMaterial?.diffuse.contents = #colorLiteral(red: 1, green: 1, blue: 1, alpha: 1)
      let sphereNode = SCNNode(geometry: sphereGeom)
      
      coordinateAxisNode.addChildNode(sphereNode)
      return coordinateAxisNode
    }
  
  
    private static func createGridNode() -> SCNNode
    {
    
      let gridNode = SCNNode();

      
  /*
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
      gridNode.addChildNode(textZNode)*/
     
      let floorNode = SCNNode(geometry: gridGeometry())
      gridNode.addChildNode(floorNode)
      return gridNode;
    }
  
    private static func gridGeometry() -> SCNGeometry
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
   
      let meshGeom =  SCNGeometry(sources: [sourcePositions, sourceTexCoords, sourceNormals], elements: [element])

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


