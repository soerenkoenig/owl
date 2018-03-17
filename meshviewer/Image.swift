//
//  Image.swift
//  MeshViewer
//
//  Created by Sören König on 16.03.18.
//  Copyright © 2018 Sören König. All rights reserved.
//

import Foundation
import AppKit

class Image: NSObject
{
  private let cpp_image_pointer: UnsafeMutableRawPointer
  
  override init () {
    self.cpp_image_pointer = image_init()
    super.init()
  }
  
  init (width : Int, height : Int) {
    self.cpp_image_pointer = image_init2(Int32(width), Int32(height))
    super.init()
  }
  
  static func createGrid(_ nx : Int,_ ny : Int,_ spacing : Int = 4) -> Image
  {
    let image = Image();
    image_create_grid(image.cpp_image_pointer, Int32(nx), Int32(ny), Int32(spacing))
    return image
  }
  
  static func createGridColor(_ nx : Int,_ ny : Int,_ spacing : Int = 4,_ xcolor: NSColor = #colorLiteral(red: 0.7450980544, green: 0.1568627506, blue: 0.07450980693, alpha: 1) ,_ zcolor: NSColor = #colorLiteral(red: 0.1019607857, green: 0.2784313858, blue: 0.400000006, alpha: 1) ) -> Image
  {
    let image = Image();
    image_create_grid_color(image.cpp_image_pointer, Int32(nx), Int32(ny), Int32(spacing),xcolor.hexUInt32, zcolor.hexUInt32)
    return image
  }
  
  deinit {
    image_deinit(self.cpp_image_pointer)
  }
  
  var width: Int
  {
    get
    {
      return Int(image_width(self.cpp_image_pointer))
    }
  }
  
  var height:Int
  {
    get
    {
      return Int(image_height(self.cpp_image_pointer))
    }
  }
  
  func image() -> CGImage?
  {
 
    let byteData = Data(bytesNoCopy: image_raw_data(self.cpp_image_pointer), count: 3*width*height, deallocator: .none)
    
    let provider : CGDataProvider  = CGDataProvider(data:byteData as CFData)!
    return CGImage(width: width, height: height, bitsPerComponent: 8, bitsPerPixel: 24, bytesPerRow: width*3, space: CGColorSpaceCreateDeviceRGB(), bitmapInfo: CGBitmapInfo(), provider: provider, decode: nil, shouldInterpolate: false, intent: .defaultIntent )
   
  }
}
