//
//  AppDelegate.swift
//  MeshViewer
//
//  Created by Sören König on 08.03.18.
//  Copyright © 2018 Sören König. All rights reserved.
//

import Cocoa

@NSApplicationMain
class AppDelegate: NSObject, NSApplicationDelegate {



  func applicationDidFinishLaunching(_ aNotification: Notification) {
    // Insert code here to initialize your application
  }

  func applicationWillTerminate(_ aNotification: Notification) {
    // Insert code here to tear down your application
  }
  
  func  application(_ sender: NSApplication, openFile filename: String) -> Bool
  {
    let myview = sender.mainWindow?.contentViewController as? ViewController
    myview?.loadMesh(filename:URL(string:filename)!)
    return true
  }
  


}

