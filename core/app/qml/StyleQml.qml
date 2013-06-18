/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0
import board.core 2.0

StyleQml {
    property color panelColor: "#E0E0E0"
    property int panelSize: 40
    property variant normalButton: normalButton
    property variant closeButton: closeButton
    property variant minimizeButton: minimizeButton

    Item {
        id: normalButton

        property Gradient normal: Gradient {
            GradientStop { position: 0; color: "#E0E0E0" }
            GradientStop { position: 0.25; color: "#B0B0B0" }
            GradientStop { position: 0.75; color: "#A0A0A0" }
            GradientStop { position: 1; color: "#808080" }
        }

        property Gradient pressed: Gradient {
            GradientStop { position: 0; color: "#606060" }
            GradientStop { position: 0.25; color: "#808080" }
            GradientStop { position: 0.75; color: "#909090" }
            GradientStop { position: 1; color: "#B0B0B0" }
        }

        property Gradient hovered: Gradient {
            GradientStop { position: 0; color: "#FFFFFF" }
            GradientStop { position: 0.25; color: "#D0D0D0" }
            GradientStop { position: 0.75; color: "#C0C0C0" }
            GradientStop { position: 1; color: "#A0A0A0" }
        }

        property Gradient disabled: Gradient {
            GradientStop { position: 0; color: "#FFFFFF" }
            GradientStop { position: 1; color: "#E0E0E0" }
        }
    }

    Item {
        id: closeButton

        property Gradient normal: Gradient {
            GradientStop { position: 0; color: "#FF0000" }
            GradientStop { position: 0.25; color: "#E00000" }
            GradientStop { position: 0.75; color: "#D00000" }
            GradientStop { position: 1; color: "#B00000" }
        }

        property Gradient pressed: Gradient {
            GradientStop { position: 0; color: "#B00000" }
            GradientStop { position: 0.25; color: "#D00000" }
            GradientStop { position: 0.75; color: "#E00000" }
            GradientStop { position: 1; color: "#FF0000" }
        }

        property Gradient hovered: Gradient {
            GradientStop { position: 0; color: "#FF8080" }
            GradientStop { position: 0.25; color: "#E07070" }
            GradientStop { position: 0.75; color: "#D06868" }
            GradientStop { position: 1; color: "#B05858" }
        }
    }

    Item {
        id: minimizeButton

        property Gradient normal: Gradient {
            GradientStop { position: 0; color: "#0000FF" }
            GradientStop { position: 0.25; color: "#0000E0" }
            GradientStop { position: 0.75; color: "#0000D0" }
            GradientStop { position: 1; color: "#0000B0" }
        }

        property Gradient pressed: Gradient {
            GradientStop { position: 0; color: "#0000B0" }
            GradientStop { position: 0.25; color: "#0000D0" }
            GradientStop { position: 0.75; color: "#0000E0" }
            GradientStop { position: 1; color: "#0000FF" }
        }

        property Gradient hovered: Gradient {
            GradientStop { position: 0; color: "#8080FF" }
            GradientStop { position: 0.25; color: "#7070E0" }
            GradientStop { position: 0.75; color: "#6868D0" }
            GradientStop { position: 1; color: "#5858B0" }
        }
    }
}
