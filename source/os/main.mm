#include <stdio.h>

#import <Virtualization/Virtualization.h>

int main() {
  auto vm_config = [[VZVirtualMachineConfiguration alloc] init];
  vm_config.CPUCount = 1;
  // VZVirtualMachineConfiguration.minimumAllowedMemorySize = 4 * 1024 * 1024;
  vm_config.memorySize = 10 * 1024 * 1024; // 10 MB
  auto serial_config =
      [[VZVirtioConsoleDeviceSerialPortConfiguration alloc] init];

  NSError* error;
  serial_config.attachment = [[VZFileSerialPortAttachment alloc]
      initWithURL:[NSURL fileURLWithPath:@"./serial_output.txt"]
           append:false
            error:&error];
  vm_config.serialPorts = @[ serial_config ];
  return 0;
}

// [NOTES]
// https://www.kernel.org/doc/Documentation/arm64/booting.txt
