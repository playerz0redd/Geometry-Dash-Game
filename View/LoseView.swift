//
//  LoseView.swift
//  test-cpp-2
//
//  Created by Pavel Playerz0redd on 25.11.24.
//

import Foundation
import SwiftUI

struct LoseView: View {
    @Binding var state: CurrentState
    @StateObject var viewModel: DrawingViewModel = .init()
    var audioPlayer: MusicCore
    var body: some View {
        Image("lose-screen-new")
            .resizable()
            .ignoresSafeArea()
            .overlay(alignment: .top) {
                VStack {
                    MenuText(size: 70, colorTop: Color(red: 252/255, green: 243/255, blue: 245/255), colorBottom: Color(red: 237/255, green: 177/255, blue: 208/255), text: "YOU LOSE\n TRY AGAIN!")
                        .padding(.bottom, 60)
                    MenuText(size: 70, colorTop: Color(red: 255/255, green: 62/255, blue: 159/255), colorBottom: Color(red: 252/255, green: 78/255, blue: 0/255), text: "SCORE: \(viewModel.userCore.currentPoints)")
                        .padding(.bottom, 150)
                    NavigationStack {
                        NavigationLink(destination: GameMenu(viewModel: viewModel, state: $state, audioPlayer: audioPlayer)) {
                            MenuButtonView(text: "MENU")
                        }.onTapGesture {
                            state = .menu
                        }.buttonStyle(PlainButtonStyle())
                    }
                }.padding(.top, 100)
            }
    }
}
