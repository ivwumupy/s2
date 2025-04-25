import SwiftUI

struct SimpleHStack: Layout {
  let spacing: CGFloat

  func sizeThatFits(
    proposal: ProposedViewSize,
    subviews: Self.Subviews,
    cache: inout Self.Cache
  ) -> CGSize {
    let idealViewSizes = subviews.map { $0.sizeThatFits(.unspecified) }

    let spacing = spacing * CGFloat(subviews.count - 1)
    let width = spacing + idealViewSizes.reduce(0) { $0 + $1.width }
    let height = idealViewSizes.reduce(0) { max($0, $1.height) }

    return CGSize(width: width, height: height)
  }

  func placeSubviews(
    in bounds: CGRect,
    proposal: ProposedViewSize,
    subviews: Self.Subviews,
    cache: inout Self.Cache
  ) {
    var pt = CGPoint(x: bounds.minX, y: bounds.minY)
    for v in subviews {
      v.place(at: pt, anchor: .topLeading, proposal: .unspecified)
      pt.x += v.sizeThatFits(.unspecified).width + spacing
    }
  }
}
