//
//  MusicCore.swift
//  test-cpp-2
//
//  Created by Pavel Playerz0redd on 21.11.24.
//

import Foundation
import AVFoundation
import SwiftUI

class MusicCore {
    var audioPlayer: AVAudioPlayer?
    var isPlaying = false
    
    init() {
        if let path = Bundle.main.path(forResource: "background-music", ofType: "mp3") {
            do {
                let url = URL(fileURLWithPath: path)
                audioPlayer = try AVAudioPlayer(contentsOf: url)
            } catch {
                print("Error initializing audio player: \(error.localizedDescription)")
            }
        } else {
            print("Audio file not found.")
        }
        
    }
    
    func playMusic() {
        isPlaying = true
        audioPlayer?.play()
    }
    
    func stopMusic() {
        isPlaying = false
        audioPlayer?.stop()
    }
    
}
