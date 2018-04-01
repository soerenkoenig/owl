import Cocoa
import SceneKit

class ViewController: NSViewController{

  @IBOutlet weak var wireframeButton: NSButton!

  @IBOutlet weak var statusText: NSTextField!
  
  @IBOutlet weak var sceneView: SCNView!
  
  @IBOutlet weak var progressIndicator: NSProgressIndicator!
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
      loadMesh(filename:openPanel.url!)
    }
  }
  
  func loadMesh(filename:URL){
     mesh?.loadMesh(url:filename.path, progressIndicator: progressIndicator)
     NSDocumentController.shared.noteNewRecentDocumentURL(filename)
  }
 
  @IBAction func showGridButtonPressed(_ sender: NSButton) {
   self.grid?.gridVisible = sender.state == .on
  }
  
   @IBAction func colorChanged(_ sender: NSColorWell) {
    self.mesh?.colorize_faces(sender.color)
    self.mesh?.update()
  }
  
  @IBAction func showCoordinateAxisPressed(_ sender: NSButton) {
    self.grid?.coordinateAxisVisible = sender.state == .on
  }
  
  @IBAction func wireFrameButtonPressed(_ sender: NSButton) {
     self.mesh?.isWireFrame = sender.state == .on
     self.mesh?.update()
  }
  
  @IBAction func faceNormalsButtonPressed(_ sender: NSButton) {
     self.mesh?.useFaceNormals = sender.state == .on
     self.mesh?.update()
  }
  
  override func keyDown(with event: NSEvent) {
    if let key = event.charactersIgnoringModifiers, key == " "
    {
      resetCamera()
    }
    
  }
  
  override func flagsChanged(with event: NSEvent) {
   if event.modifierFlags.contains(.shift)
    {
      sceneView.allowsCameraControl = false;
    }
    else
    {
      sceneView.allowsCameraControl = true;
    }
  }
  
  override func mouseDown(with event: NSEvent) {
    let local_point = sceneView.convert(event.locationInWindow, from: nil)
    let pNear = sceneView.unprojectPoint(SCNVector3(local_point.x, local_point.y, 0.0));
    let pFar = sceneView.unprojectPoint(SCNVector3(local_point.x, local_point.y, 1.0));
    let source = SCNGeometrySource(vertices: [pNear, pFar])
    let element = SCNGeometryElement(indices: [0, 1], primitiveType: .line)
    let geometry = SCNGeometry(sources: [source], elements: [element])
    geometry.firstMaterial?.lightingModel = .constant
    geometry.firstMaterial?.diffuse.contents = #colorLiteral(red: 1, green: 1, blue: 1, alpha: 1)
    sceneView.scene?.rootNode.addChildNode(SCNNode(geometry: geometry));
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
 
    mesh = Mesh()
    scene.rootNode.addChildNode((mesh?.meshNode)!)
    loadMesh(filename:URL(string:"/Users/skoenig/Downloads/bun_zipper.ply")!)
    sceneView.scene = scene
    sceneView.autoenablesDefaultLighting = true
    sceneView.allowsCameraControl = true
    sceneView.cameraControlConfiguration.allowsTranslation = true
    sceneView.backgroundColor = #colorLiteral(red: 0.05882352963, green: 0.180392161, blue: 0.2470588237, alpha: 1)
  }


}

