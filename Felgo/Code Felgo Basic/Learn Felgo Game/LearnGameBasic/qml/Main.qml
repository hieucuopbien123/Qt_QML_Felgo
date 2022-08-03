import Felgo 3.0
import QtQuick 2.0
import "./entities"

GameWindow {
    //default window chứa các scene và component
    id: gameWindow

    EntityManager {
        id: entityManager
        entityContainer: scene
    }
    activeScene: scene//chỉ định cái scene nào hiện tại đang đc hiện ra
    //entity là các object tương tác với game, với ng dùng và các entities khác. Với mỗi entity ta cần kiểm soát dịch
    //chuyển vật lý, animation,sound,effect,...
    //VD: EntityBase dưới là 1 entity, nó cx chỉ là 1 container chứa các component tạo thành 1 entity có id và type
    //id cần để xóa entity sau này, còn type dùng để check va chạm chẳng hạn-> nch là phải định nghĩa 2 thuộc tính này
    //cho mỗi entity
    //EntityManager sẽ quản lý các EntityBase, entityContainer là nơi chứa các EntityBase đó. Phải khai báo cái này ngay khi
    //entity được định nghĩa vì các entity được tạo ra at runtime cần biết nó phải đc add vào trong component container nào

    Rectangle {
      anchors.fill: parent
      color: "black"
    }

    onSplashScreenFinished: world.running = true//App cx có
    Scene {
        id: scene
        PhysicsWorld {
            //PhysicsWorld kế thừa từ world biểu diễn physicalworld chứa các vật lý
            id: world
            running: false// physics is disabled initially, and enabled after the splash is finished
            gravity.y: 9.81//set trọng lực cho world như trong vật lý->tăng y là tăng gia tốc rơi nhanh hơn

            //Mỗi physical Component có 1 cái Debug View để debug chuyển động vật lý, nó là hẳn 1 component trong felgo luôn
            //nó sẽ hiển thị bodies, joints, lực
            debugDrawVisible: true

            z: 1 //debug draw sẽ đảm bảo hiển thị bên trên entity, mặc định là 1 r

            //update bao nhiêu lần trong 1s-> cái này như framerate v, dùng tầm 30 là mức trung bình, càng cao càng dễ giật lag
            //nên tăng dần lên đến khi thấy phù hợp, default là 30
            updatesPerSecondForPhysics: 30
            //số lần thay đổi vận tốc và vị trí cũng ảnh hưởng đến performance, mặc định là 5. Tăng hay giảm cho phù hợp
            velocityIterations: 5
            positionIterations: 5
        }
        property int createdBoxes: 1
        property real safetyDistance: -1
        Text {
             text: "Boxes: " + scene.createdBoxes
             color: "white"
             z: 1
         }
        Timer {
              id: timer
              interval: Math.random()*3000 + 2000
              running: true // start running from the beginning, when the scene is loaded
              repeat: true
              onTriggered: {
                  var newEntityProperties = {
                      x: Math.random()*(scene.width-2*50) + 50,//trả ra randon từ 0-1
                      y: 50, // position on top of the scene, at least below the top wall
                      rotation: Math.random()*360
                  }

                  entityManager.createEntityFromUrlWithProperties(
                              Qt.resolvedUrl("entities/Box.qml"),
                              newEntityProperties);//hàm tạo entity mới
                  scene.createdBoxes++

                  //vì cái kia là fix mà, thế thì mỗi lần chạy random đc mỗi lần xong lại giống nhau nên ta phải lại
//                  interval = Math.random()*3000 + 2000
                  interval = generateRandomInterval()

                  timer.restart()//phải restart để cập nhập giá trị mới
              }
              function generateRandomInterval() {
                // recalculate new interval between 1000 and 3000
                return utils.generateRandomValueBetween(2000, 5000);
              }
          }

        Column {
          anchors.right: parent.right
          spacing: 5
          z: 1
          //cái này render trc nên bị wall đè-> cho nó xuống dưới or chỉnh z là đc
          SimpleButton {
            text: "Toggle Audio"
            onClicked: {
                settings.soundEnabled = !settings.soundEnabled
            }
            anchors.right: parent.right
          }
          SimpleButton {
            text: "Toggle Particles"
            onClicked: settings.particlesEnabled = !settings.particlesEnabled
            //chú ý cái settings này nguy hiểm, setting false phát là mọi dự án khác dùng đều k đc luôn
          }
        }

        Box{
            x: scene.width/2
            y: 50
        }

        Wall {
           // left wall
           width: 20
           height: scene.height
           anchors {
               left: scene.left
           }
       }
       Wall {
           // right wall
           width: 20
           height: scene.height
           anchors {
               right: scene.right
           }
       }
       Wall {
           // top wall
           height: 20
           width: scene.width
           anchors {
               top: scene.top
           }
           color: "red" // make the top wall red
           onCollidedWithBox: {
               // gets called when the wall collides with a box, and the game should restart

               // remove all entities of type "box", but not the walls
               entityManager.removeEntitiesByFilter(["box"]);
               // reset the createdBoxes amount
               scene.createdBoxes = 0;
           }
       }

        EntityBase {
            entityId: "ground1"
            entityType: "ground"
            height: 20
            anchors {
                bottom: scene.bottom
                left: scene.left
                right: scene.right
            }

            Rectangle {
                anchors.fill: parent
                color: "blue"
            }
            BoxCollider {
                anchors.fill: parent
                bodyType: Body.Static//thanh cố định k bị ảnh hưởng bởi thế giới vật lý, mặc định đc set là dynamic
            }
        }//viết 2 entity rời nhau sẽ tự có tương tac với nhau trong thế giới vật lý

        Component {
            id: mouseJoint
            MouseJoint {
                //MouseJoint kiểm soát cái di chuyển bằng chuột or touch
                maxForce: 30000*world.pixelsPerMeter
                //box2d dung meter làm đơn vị khoảng cách, lực, vận tốc, mặc định là 32 pixel 1 mét
                //lực lớn nhất dùng để move đối tượng(có liên quan đến khối lượng) càng lớn move càng nhanh
                //kp độ nhạy-> nếu lực quá nhỏ thậm chí còn chẳng nhấc nổi vật nx
                dampingRatio: 1//The damping ratio. 0 = no damping, 1 = critical damping. Default is 0.7
                // The response speed, default is 5
                frequencyHz: 2 // mức độ nhay tới targetPoint, mặc định là 5
            }
            //Đây là ta chỉ set các thuộc tính cho 1 kiểu component, ta sẽ dùng nó như 1 thuộc tính trong 1 component
            //khác như dưới(thg là MouseArea).
            //Dùng kiểu này sẽ tái sử dụng chứ khai báo luôn trong MouseArea cx đc nhưng chỉ dùng 1 lần nv
            //Tức là MouseJoint này có thể nhét vào 1 file khác r khai báo trong Component như này
            //Component này phải đc đặt trong 1 PhysicsWorld để dùng nó
        }

        // when the user presses a box, move it towards the touch position
        MouseArea {
            anchors.fill: parent

            property Body selectedBody: null
            property MouseJoint mouseJointWhileDragging: null
            onPressed: {
                selectedBody = world.bodyAt(Qt.point(mouseX, mouseY));
                console.debug("selected body at position", mouseX, mouseY, ":", selectedBody);
                // if the user selected a body, this if-check is true vì selectedBody sẽ tồn tại khác null
                if(selectedBody) {
                    // create a biến mouseJoint mới
                    mouseJointWhileDragging = mouseJoint.createObject(world)
                    //đặt trong parent là world

                    // set the target position to the current touch position (initial position)
                    mouseJointWhileDragging.target = Qt.point(mouseX, mouseY)

                    // connect the joint with the body
                    mouseJointWhileDragging.bodyB = selectedBody
                    //bodyB là body ta cần move tới target, tạo->set move cái gì->set target là cái gì là đc

                    /*var properties = {
                        // set the target position to the current touch position (initial position)
                        target: Qt.point(mouseX, mouseY),

                        // body B is the one that actually moves -> connect the joint with the body
                        bodyB: selectedBody
                      }

                      mouseJointWhileDragging = mouseJoint.createObject(physicsWorld, properties)
                      //bởi vì createObject nó cx có đối số 2 là object mà*/
                }
            }

            onPositionChanged: {
                // this check is necessary, because the user might also drag when no initial body was selected
                if (mouseJointWhileDragging)
                    mouseJointWhileDragging.target = Qt.point(mouseX, mouseY)
            }
            onReleased: {
                if(selectedBody) {
                    selectedBody = null
                    if (mouseJointWhileDragging)
                        mouseJointWhileDragging.destroy()//tạo mới và huy liên tục khi click nhả
                }
            }
        }
    }
}
//utils sẽ provides often-needed functionality như random (giống kiểu global qt)
