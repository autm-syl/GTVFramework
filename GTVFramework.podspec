Pod::Spec.new do |s|
  s.name             = 'GTVFramework'
  s.version          = '0.1.0'
  s.summary          = 'GTVFramework!'


  s.description      = "GTVFramework use for gtv's partner. support ios version > 10.0"

  s.homepage         = 'https://github.com/autm-syl/GTVFramework'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'autm-syl' => 'cuonglv@gametv.com.vn' }
  s.source           = { :git => 'https://github.com/autm-syl/GTVFramework.git', :tag => s.version.to_s }
  s.social_media_url = 'https://gtv.com.vn/'

  
  s.frameworks = 'UIKit', 'AudioToolbox', 'WebKit', 'GLKit', 'CoreMedia', 'StoreKit', 'SystemConfiguration', 'AVFoundation', 'CFNetwork', 'MapKit'
  s.libraries = 'icucore', 'c++'
  
  s.requires_arc        = true
  s.ios.deployment_target = '10.0'
  s.platform            = :ios, '10.0'
  
  s.source              = { :http => "https://github.com/duplicater/MdcLib-Skyprepare/releases/download/#{s.version}/MdcLib.zip" }

  s.source_files = 'GTVFramework/Classes/**/*'
end
