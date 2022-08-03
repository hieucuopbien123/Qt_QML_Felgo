import QtQuick 2.0

Rectangle {
    width: 100
    height: 100
    color: "limegreen"
    id: box
    SequentialAnimation {
        running: true
        RotationAnimation {
            target: box
            property: "rotation"
            from: 0
            to: 360
            duration: 500
        }

        ColorAnimation {
            target: box
            property: "color"
            to: "blue"
            duration: 500
        }
    }
    NumberAnimation on x {//tức x là thuộc tính của cha nên k dùng cách này trong SequentialAnimation đc
        to: root.width - 2* box.width//éo dùng đc this với parent trong animation
        duration: 1000
        running: true
        easing.period: 0.5
        easing.amplitude: 0.3
        easing.type: Easing.InOutBack
    }
    NumberAnimation {
        target: box
        properties: "opacity"
        loops: Animation.Infinite
        duration: 5000
        from: 0.5
        to: 1
        running: true//mặc định running là false ms vl
        easing.type: Easing.InOutElastic
        easing.amplitude: 2.0;
        easing.period: 1.5
    }//muốn lượt về từ 1 đến 0.5 thì lại thêm 1 cái nx song song
}
