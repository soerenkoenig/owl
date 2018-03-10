//
//  ViewController.swift
//  MeshViewer
//
//  Created by Sören König on 08.03.18.
//  Copyright © 2018 Sören König. All rights reserved.
//

import Cocoa
import SceneKit

class ViewController: NSViewController {

  @IBOutlet weak var sceneView: SCNView!
  
  override func viewDidLoad() {
    super.viewDidLoad()

    sceneSetup()
  }

  override var representedObject: Any? {
    didSet {
    // Update the view, if already loaded.
    }
  }
  
  func sceneSetup() {
   
    
    let scene = SCNScene()
    
   /* let floorGeometry = SCNFloor();
    let floorNode = SCNNode(geometry: floorGeometry)
    scene.rootNode.addChildNode(floorNode)
    */
    let cameraNode = SCNNode()
    cameraNode.camera = SCNCamera()
    cameraNode.position = SCNVector3Make(20, 10, 1)
    scene.rootNode.addChildNode(cameraNode)
    cameraNode.look(at:SCNVector3(0,0,0));
    
    let boxGeometry = SCNBox(width: 4.0, height: 4.0, length: 4.0, chamferRadius: 0.0)
    let boxNode = SCNNode(geometry: boxGeometry)
    boxNode.position = SCNVector3(0,2.0,0)
  //  scene.rootNode.addChildNode(boxNode)
    boxGeometry.firstMaterial!.diffuse.contents = #colorLiteral(red: 0.2745098174, green: 0.4862745106, blue: 0.1411764771, alpha: 1)
    
    let indices: [Int32] = [0, 1, 2, 3]
    let vector1 = SCNVector3(0,0,0);
    let vector2 = SCNVector3(0,10,0);
    let vector3 = SCNVector3(0.5,10,0);
    let vector4 = SCNVector3(0.5,0,0);
    
    let source = SCNGeometrySource(vertices: [vector1, vector4,vector2, vector3])
    let element = SCNGeometryElement(indices: indices, primitiveType: .triangleStrip)

    let lineGeom =  SCNGeometry(sources: [source], elements: [element])
    let lineNode = SCNNode(geometry: lineGeom)
    
    lineGeom.firstMaterial?.lightingModel = SCNMaterial.LightingModel.constant
    lineGeom.firstMaterial?.diffuse.contents  = #colorLiteral(red: 0.9254902005, green: 0.2352941185, blue: 0.1019607857, alpha: 1)
 //   scene.rootNode.addChildNode(lineNode);
    lineNode.constraints = [SCNBillboardConstraint()]
    
    
     let m = Mesh()
     m.create_geo_sphere()
    //  m.create_box()
  //  let result = m.load("test.txt")
  //  print(result)
    
    print("number of vertices: \(m.vertexCount)")
    print("number of edges: \(m.edgeCount)")
    print("number of halfedges: \(m.halfedgeCount)")
    print("number of faces: \(m.faceCount)")
    
    let meshGeom = m.edgeGeometry()
    let meshNode = SCNNode(geometry: meshGeom)
    meshGeom.firstMaterial?.lightingModel = SCNMaterial.LightingModel.constant
    meshGeom.firstMaterial?.diffuse.contents  = #colorLiteral(red: 0.9254902005, green: 0.2352941185, blue: 0.1019607857, alpha: 1)
    meshNode.renderingOrder = 100000;
    scene.rootNode.addChildNode(meshNode)
    
    
    sceneView.scene = scene
    sceneView.autoenablesDefaultLighting = true
    sceneView.allowsCameraControl = true
    sceneView.backgroundColor = #colorLiteral(red: 0.2745098174, green: 0.4862745106, blue: 0.1411764771, alpha: 1)
    
    print(meshNode.boundingBox)
  }


}

