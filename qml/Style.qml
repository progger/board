/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1

Item {
    property Gradient gradientButtonNormal: Gradient {
        GradientStop { position: 0; color: "#E0E0E0" }
        GradientStop { position: 0.25; color: "#B0B0B0" }
        GradientStop { position: 0.75; color: "#A0A0A0" }
        GradientStop { position: 1; color: "#808080" }
    }

    property Gradient gradientButtonPressed: Gradient {
        GradientStop { position: 0; color: "#606060" }
        GradientStop { position: 0.25; color: "#808080" }
        GradientStop { position: 0.75; color: "#909090" }
        GradientStop { position: 1; color: "#B0B0B0" }
    }

    property Gradient gradientButtonHovered: Gradient {
        GradientStop { position: 0; color: "#FFFFFF" }
        GradientStop { position: 0.25; color: "#D0D0D0" }
        GradientStop { position: 0.75; color: "#C0C0C0" }
        GradientStop { position: 1; color: "#A0A0A0" }
    }

    property color panelColor: "#C0C0C0"
    property int panelSize: 44
}
