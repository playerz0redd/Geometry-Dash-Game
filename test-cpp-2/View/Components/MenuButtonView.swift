//
//  MenuButtonView.swift
//  test-cpp-2
//
//  Created by Pavel Playerz0redd on 21.11.24.
//

import Foundation
import SwiftUI

struct MenuButtonView: View {
    var text: String = ""
    var body: some View {
        Text("\(text)")
            .font(.system(size: 24, weight: .bold))
            .foregroundColor(.white)
            .padding()
            .frame(width: 200, height: 60)
            .background(
                LinearGradient(gradient: Gradient(colors: [Color.orange, Color.pink]),
                               startPoint: .topLeading,
                               endPoint: .bottomTrailing)
            )
            .cornerRadius(30)
            .shadow(color: Color.black.opacity(0.2), radius: 10, x: 0, y: 5)
    }
}
