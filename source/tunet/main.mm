#import <CoreLocation/CoreLocation.h>
#import <CoreWLAN/CoreWLAN.h>

int main() {
  auto location = [[CLLocationManager alloc] init];
  NSLog(@"%d", location.authorizationStatus);
  [location requestWhenInUseAuthorization];
  NSLog(@"%d", location.authorizationStatus);

  auto client = [CWWiFiClient sharedWiFiClient];
  auto interface = [client interface];

  // https://developer.apple.com/forums/thread/732431
  //
  // SSID information is not available unless Location Services is enabled and
  // the user has authorized the calling app to use location services.
  NSLog(@"%@", interface.ssid);
  return 0;
}
