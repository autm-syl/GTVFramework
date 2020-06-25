Pod::Spec.new do |s|
  s.name             = 'GTVFramework'
  s.version          = '0.1.1'
  s.summary          = 'GTVFramework!'
  
  s.description      = "GTVFramework use for gtv's partner. support ios version > 10.0"

  s.homepage         = 'https://github.com/autm-syl/GTVFramework'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'autm-syl' => 'cuonglv@gametv.com.vn' }
  s.source           = { :git => 'https://github.com/autm-syl/GTVFramework.git', :tag => s.version.to_s }
  s.social_media_url = 'https://gtv.com.vn/'

  
  s.frameworks = 'UIKit', 'AudioToolbox', 'WebKit', 'GLKit', 'CoreMedia', 'StoreKit', 'SystemConfiguration', 'AVFoundation', 'CFNetwork', 'MapKit'
  s.libraries = 'icucore', 'c++'
  
  
  s.dependency 'AppsFlyerFramework', '~>5.3.0'
  s.dependency 'Firebase/Analytics'
  s.dependency 'Firebase/Messaging'
  s.dependency 'Firebase/DynamicLinks'
  s.dependency 'FBSDKCoreKit', '~>7.0.1'
  s.dependency 'FBSDKLoginKit', '~>7.0.1'
  s.dependency 'FBSDKShareKit', '~>7.0.1'
  s.dependency 'AFNetworking', '~> 4.0'

  
  s.requires_arc        = true
  s.ios.deployment_target = '10.0'
  s.platform            = :ios, '10.0'
  
  s.source              = { :http => "https://github.com/autm-syl/GTVFramework/releases/download/#{s.version}/GTV.zip" }

  s.preserve_paths      = 'GTVLib.framework'
  s.public_header_files = 'GTVLib.framework/Versions/A/Headers/*'
  s.source_files        = 'GTVLib.framework/Versions/A/Headers/*'
  s.resource    = 'GTVLib.Bundle'
  s.vendored_frameworks = 'GTVLib.framework'
end
