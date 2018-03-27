import Cocoa
import SceneKit

class ViewController: NSViewController{

  @IBOutlet weak var wireframeButton: NSButton!

  @IBOutlet weak var statusText: NSTextField!
  
  @IBOutlet weak var sceneView: SCNView!
  
  var meshNode: SCNNode?
  var mesh: Mesh?
  var grid: Grid?
  
  override func viewDidLoad() {
    super.viewDidLoad()
    sceneSetup()
    resetCamera()
  }
  
  @IBAction func openDocument(_ sender: NSMenuItem) {
   let openPanel = NSOpenPanel()
    openPanel.allowsMultipleSelection = false
    openPanel.canChooseDirectories = false
    openPanel.canCreateDirectories = false
    openPanel.canChooseFiles = true
    openPanel.allowedFileTypes = ["off","ply"]
    let i = openPanel.runModal()
    if(i == NSApplication.ModalResponse.OK)
    {
      print(openPanel.url!)
     
      loadMesh(url:openPanel.url!.path)
      NSDocumentController.shared.noteNewRecentDocumentURL(openPanel.url!)
    }
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
  
  func loadMesh(url: String){
    statusText.stringValue = "Status: Loading mesh \(url)"
    let indicator: NSProgressIndicator = NSProgressIndicator(frame: NSRect(x: 10, y: 10, width: 400, height: 400));
    //indicator.autoresizingMask =  NSViewHeightSizable | NSViewWidthSizable
    indicator.usesThreadedAnimation = true
    self.view.addSubview(indicator)
    indicator.isBezeled = true
    indicator.style = .spinning
    indicator.controlTint = .clearControlTint
    indicator.startAnimation(self)
    
   
   DispatchQueue.global(qos: .background).async {
      self.mesh = Mesh.load(filename:url)
      self.mesh!.auto_center_and_scale()
      self.mesh?.triangulate()
    
    
      DispatchQueue.main.async{
          self.meshNode?.geometry = self.mesh?.triangleGeometry()
          print("Mesh statistics: # faces = \(self.mesh!.faceCount), # vertices = \(self.mesh!.vertexCount)")
          indicator.stopAnimation(self)
          indicator.removeFromSuperview()
          self.statusText.stringValue = "Status: idle"
      }
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
    // self.mesh = Mesh.create_tetrahedron()
    // self.mesh = Mesh.create_box()
    // self.mesh?.triangulate()
 
   // let meshGeom = mesh?.triangleGeometry()
    self.meshNode = SCNNode()
    scene.rootNode.addChildNode(meshNode!)
    loadMesh(url:"/Users/skoenig/Downloads/bun_zipper.ply")
    sceneView.scene = scene
    sceneView.autoenablesDefaultLighting = true
    sceneView.allowsCameraControl = true
    sceneView.cameraControlConfiguration.allowsTranslation = true
    sceneView.backgroundColor = #colorLiteral(red: 0.05882352963, green: 0.180392161, blue: 0.2470588237, alpha: 1)
  }


}

