import QtQuick 2.0
import Felgo 3.0

EntityBase {
  entityType: "wall"

  signal collidedWithBox

  property alias color: rectangle.color

  property alias collider: collider

  Rectangle {
    id: rectangle
    color: "blue"
    anchors.fill: parent
  }
  BoxCollider {
    id: collider
    anchors.fill: parent
    bodyType: Body.Static

    fixture.onBeginContact: collidedWithBox()
  }
}
