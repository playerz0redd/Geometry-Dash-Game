//
//  RecordsView.swift
//  test-cpp-2
//
//  Created by Pavel Playerz0redd on 25.11.24.
//

import Foundation
import SwiftUI

struct RecordsView: View {
    var recordsArr: [Int]
    @Binding var state: CurrentState
    var body: some View {
        ScrollView {
            VStack {
                MenuText(size: 50, colorTop: .red, colorBottom: .yellow, text: "RECORDS")
                ForEach(recordsArr, id: \.self) { record in
                    Divider()
                    Text("\(record)")
                        .font(.system(size: 20))
                        .italic()
                        .foregroundStyle(LinearGradient(
                            colors: [Color(red: 1, green: 62/255, blue: 159/255), Color(red: 254/255, green: 69/255, blue: 11/255)],
                            startPoint: .top,
                            endPoint: .bottom
                        ))
                }
                Divider()
                    
                Button {
                    state = .menu
                } label: {
                    MenuButtonView(text: "EXIT")
                        .padding(.top, 40)
                        .padding(.bottom, 40)
                }.buttonStyle(PlainButtonStyle())
            }
            .ignoresSafeArea()
        }
        .frame(maxWidth: .infinity, maxHeight: .infinity)
        .ignoresSafeArea()
        .background(LinearGradient(
            colors: [Color(red: 1, green: 1, blue: 1), Color(red: 86/255, green: 36/255, blue: 110/255)],
            startPoint: .top,
            endPoint: .bottom
        ))
        .ignoresSafeArea()
    }
}
