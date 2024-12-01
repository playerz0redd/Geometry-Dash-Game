//
//  MenuText.swift
//  test-cpp-2
//
//  Created by Pavel Playerz0redd on 21.11.24.
//

import Foundation
import SwiftUI


struct MenuText: View {
    var size: CGFloat
    var colorTop: Color
    var colorBottom: Color
    var text: String
    var body: some View {
        Text(text)
            .font(Font.system(size: size, weight: .bold))
            .multilineTextAlignment(.center)
            .overlay {
                LinearGradient(
                    colors: [colorTop, colorBottom],
                    startPoint: .top,
                    endPoint: .bottom
                ).mask(
                    Text(text)
                        .font(Font.system(size: size, weight: .bold))
                        .multilineTextAlignment(.center)
                )
            }
    }
}

// Color(red: 255/255, green: 62/255, blue: 159/255)
// Color(red: 254/255, green: 69/255, blue: 11/255)
