import Cocoa
import SceneKit

class ViewController: NSViewController{

  @IBOutlet weak var wireframeButton: NSButton!
  
  @IBOutlet weak var showGridButton: NSButton!
  
  @IBOutlet weak var sceneView: SCNView!
  
  var meshNode: SCNNode?
  var mesh: Mesh?
  var grid: Grid?
  
  override func viewDidLoad() {
    super.viewDidLoad()
    sceneSetup()
    resetCamera()
  }
 
  @IBAction func showGridButtonPressed(_ sender: NSButton) {
   self.grid?.gridVisible = sender.state == .on
  }
  
  @IBAction func wireFrameButtonPressed(_ sender: NSButton) {
    if sender.state == .on
    {
      meshNode?.geometry = mesh?.edgeGeometry()
      meshNode?.geometry?.firstMaterial?.lightingModel = SCNMaterial.LightingModel.constant
      meshNode?.geometry?.firstMaterial?.diffuse.contents  = #colorLiteral(red: 0.8446564078, green: 0.5145705342, blue: 1, alpha: 1)
    }
    else
    {
      meshNode?.geometry?.firstMaterial?.lightingModel = SCNMaterial.LightingModel.blinn
      meshNode?.geometry = mesh?.triangleGeometry()
    }
  }
  @IBAction func showCoordinateAxisPressed(_ sender: NSButton) {
    self.grid?.coordinateAxisVisible = sender.state == .on
  }
  
  
  
 /* override var representedObject: Any? {
    didSet {
    // Update the view, if already loaded.
    }
  }*/
  
  override func keyDown(with event: NSEvent) {
    if let key = event.charactersIgnoringModifiers, key == " "
    {
      resetCamera()
    }
  }
  
  func resetCamera() {
    sceneView.pointOfView?.position = SCNVector3Make(0, 15, 15)
    sceneView.pointOfView?.look(at:SCNVector3(0,0,0), up: SCNVector3(0,1,0), localFront: SCNVector3(0,0,-1))
  }
  
  func sceneSetup() {
    let scene = SCNScene()
    grid = Grid()
    scene.rootNode.addChildNode((grid?.coordinateAxisNode)!)
    scene.rootNode.addChildNode((grid?.gridNode)!)
 
    let cameraNode = SCNNode()
    cameraNode.camera = SCNCamera()
    cameraNode.camera?.automaticallyAdjustsZRange = true
    cameraNode.position = SCNVector3Make(20, 10, 1)
    cameraNode.look(at:SCNVector3(0,0,0), up: SCNVector3(0,1,0), localFront: SCNVector3(0,0,-1))
    scene.rootNode.addChildNode(cameraNode)
  
   // self.mesh = Mesh.create_geo_sphere(radius: 4, numLevels: 5)
    
    // self.mesh = Mesh.create_torus(radius1:1, radius2:2)
    
    self.mesh = Mesh.load(filename:"/Users/skoenig/Downloads/Armadillo.ply")
    // self.mesh = Mesh.create_tetrahedron()
    // self.mesh = Mesh.create_box()
    self.mesh?.triangulate()
 
    let meshGeom = mesh?.triangleGeometry()
    self.meshNode = SCNNode(geometry: meshGeom)
    self.meshNode!.position = SCNVector3(0,(self.meshNode!.boundingBox.max.y - self.meshNode!.boundingBox.min.y) / 2 ,0)
    scene.rootNode.addChildNode(meshNode!)
    
    sceneView.scene = scene
    sceneView.autoenablesDefaultLighting = true
    sceneView.allowsCameraControl = true
    sceneView.backgroundColor = #colorLiteral(red: 0.05882352963, green: 0.180392161, blue: 0.2470588237, alpha: 1)
  }


}

