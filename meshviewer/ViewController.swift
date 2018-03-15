//
//  ViewController.swift
//  MeshViewer
//
//  Created by Sören König on 08.03.18.
//  Copyright © 2018 Sören König. All rights reserved.
//

import Cocoa
import SceneKit

class ViewController: NSViewController{

  @IBOutlet weak var wireframeButton: NSButton!
  
  @IBOutlet weak var showGridButton: NSButton!
  
  @IBOutlet weak var sceneView: SCNView!
  
  var meshNode: SCNNode?
  var mesh: Mesh?
  
  override func viewDidLoad() {
    super.viewDidLoad()
    sceneSetup()
    resetCamera()
  }
  @IBAction func wireFrameButtonPressed(_ sender: NSButton) {
    if sender.state == .on
    {
      meshNode?.geometry = mesh?.edgeGeometry()
      meshNode?.geometry?.firstMaterial?.lightingModel = SCNMaterial.LightingModel.constant
      meshNode?.geometry?.firstMaterial?.diffuse.contents  = #colorLiteral(red: 0.9254902005, green: 0.2352941185, blue: 0.1019607857, alpha: 1)
      print("wireframe on")
    }
    else
    {
      meshNode?.geometry = mesh?.triangleGeometry()
      print("wireframe off")
    }
  }
  
  override var representedObject: Any? {
    didSet {
    // Update the view, if already loaded.
    }
  }
  
  override func keyDown(with event: NSEvent) {
    if let key = event.charactersIgnoringModifiers, key == " "
    {
      resetCamera()
    }
  }
  
  func resetCamera()
  {
    sceneView.pointOfView?.position = SCNVector3Make(20, 10, 1)
    sceneView.pointOfView?.look(at:SCNVector3(0,0,0), up: SCNVector3(0,1,0), localFront: SCNVector3(0,0,-1))
  //  sceneView.pointOfView?.look(at:SCNVector3(0,0,0));
  }
  
  func sceneSetup() {
   
    
    let scene = SCNScene()
    let grid = Grid()
    let floorGeometry = grid.geometry();
    let floorNode = SCNNode(geometry: floorGeometry)
    scene.rootNode.addChildNode(floorNode)
   /* floorGeometry.firstMaterial?.lightingModel = SCNMaterial.LightingModel.constant
    floorGeometry.firstMaterial!.diffuse.contents = #colorLiteral(red: 0.05882352963, green: 0.180392161, blue: 0.2470588237, alpha: 1)*/
    
    let cameraNode = SCNNode()
    cameraNode.camera = SCNCamera()
    cameraNode.position = SCNVector3Make(20, 10, 1)
    cameraNode.look(at:SCNVector3(0,0,0), up: SCNVector3(0,1,0), localFront: SCNVector3(0,0,-1))
    scene.rootNode.addChildNode(cameraNode)
  
 
    // let m = Mesh.create_geo_sphere(radius: 4, numLevels: 5)
   //
   
     self.mesh = Mesh.create_torus(radius1:1, radius2:2)
    // self.mesh = Mesh.create_tetrahedron()
    // let m =   Mesh.create_box()
     self.mesh?.triangulate()
    //  m.create_box()
    print("number of vertices: \(self.mesh!.vertexCount)")
    print("number of edges: \(self.mesh!.edgeCount)")
    print("number of halfedges: \(self.mesh!.halfedgeCount)")
    print("number of faces: \(self.mesh!.faceCount)")
    
    let meshGeom = self.mesh!.edgeGeometry()
//let meshGeom = m.triangleGeometry()
    self.meshNode = SCNNode(geometry: meshGeom)
    self.meshNode!.position = SCNVector3(0,(self.meshNode!.boundingBox.max.y - self.meshNode!.boundingBox.min.y) / 2 ,0)
    meshGeom.firstMaterial?.lightingModel = SCNMaterial.LightingModel.constant
    meshGeom.firstMaterial?.diffuse.contents  = #colorLiteral(red: 0.9254902005, green: 0.2352941185, blue: 0.1019607857, alpha: 1)
    scene.rootNode.addChildNode(meshNode!)
    
    
    sceneView.scene = scene
    sceneView.autoenablesDefaultLighting = true
    sceneView.allowsCameraControl = true
    sceneView.backgroundColor = #colorLiteral(red: 0.1019607857, green: 0.2784313858, blue: 0.400000006, alpha: 1)
    
    print(meshNode!.boundingBox)
  }


}

