import SwiftUI

struct ContentView : View {
  var body: some View {
    VStack(spacing: 20) {

      HStack(spacing: 5) {
        contents()
      }
      .border(.blue)

      SimpleHStack(spacing: 5) {
        contents()
      }
      .border(.blue)

    }
    .frame(maxWidth: .infinity, maxHeight: .infinity)
    .background(.white)
  }

  @ViewBuilder func contents() -> some View {
    Image(systemName: "globe.americas.fill")
    Text("Hello, World!")
    Image(systemName: "globe.europe.africa.fill")
  }
}
