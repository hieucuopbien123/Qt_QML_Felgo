import QtQuick 2.0
import Felgo 3.0

EntityBase {//class nền của tất các entities trong game
    id: box
    //box 1 được load khi scene được load
    entityType: "box"
    //entityId là cái unique của mỗi entity(kiểu id nhưng khác vì ta truy cập id bth rồi nên k chưa dùng nó làm
    //j hết). entityType là thuộc tính chung của các entity cùng 1 nhóm, vd click 1 nút thì xóa tất cả các entity
    //có type là box chẳng hạn thì các entity cùng type box sẽ bị xóa
    width: 32
    height: 32

    transformOrigin: Item.TopLeft//origionPoint cho scale and rotation
    //cái này là đề phòng nếu dùng xoay thì cái tâm xoay mặc định là Item.Center bh nó sẽ thành bottoRight-> ta chỉnh lại
    //nó về đúng vị trí thôi dù ở đây t k dùng

    //kích thước thật ra y hệt như những gì đã học chả có gì mới.
    //entity là 1 container, nếu k set kích thước thì sẽ là 0,0. Các con bên trong có thể in thoải mái ra ngoài nó
    //đều đc
    //Các component k set vị trí sẽ mặc định là 0,0; k set kích thước mặc định là 0,0 or theo content bên trong
    //->cái này là từ qml bth rồi
    //Chỉ có BoxCollider kích thước sẽ tự động là parent nếu k set
    //=> ta có thể tùy biến thoái mái rồi, thích set kích thước cho entity hay k đều đc

    Image {
        id: boxImage
        source: "../../assets/img/box.png"
        anchors.fill: boxCollider
    }
    BoxCollider {
        id: boxCollider
        //Bản chất, entity là 1 Component có vị trí chỉ 1 điểm duy nhất mặc định là góc trái trên của component con bên trong
        //=>đó là mặc định của qml vì k set kích thước sẽ mđ là 0,0 còn con bên trong k set vị trí mặc định là 0,0
        //chứ cái này éo phải tính chất gì mới
        //các component con bên trong sẽ có kích thước và vị trí vật lý riêng. anchors.centerIn là lấy tâm của cái này trùng
        //với tâm của component nào(kể cả component đó là 1 điểm or 1 hình to chả ảnh hưởng). Khi dùng particle start trong
        //1 componnent nào đó thì nó sẽ nằm ở (0,0) component đó mặc định(có thể set x,y để đổi mà)
        //thay vì set kích thước của image r cho BoxCollider fill nó ta cho image fill cái kích thước của collider như này cx
        //đc. Ở đây ta set thêm tâm của BoxCollider trùng vào tâm entity, như thế sẽ khiến entity là parent ra giữa thì về sau
        //mọi thứ thao tác dùng entity sẽ dễ hơn ví dụ cho particle phát ra từ tâm như này. Ta hoàn toàn có thể tùy biến để điểm
        //entity ở góc trái trên r cho x,y của particle ra giữa đc chả sao
        //Tuy nhiên nếu ta muốn xét kích thước cho entity r cho các con theo nó cx đc chả sao
//        width: 32
//        height: 32//tự theo kích thước của entit

        x: -width/2
        y: -height/2

        friction: 0.1//mặc định là 0-1 -> default là 0.2-> nếu đặt là 0 thì k có ma sát với các entity khác. Nếu
        //2 vật đều có friction thì sẽ nhân với nhau
        restitution: 0//mặc định là 0, chạy 0-1 => càng lớn càng bounce
        density: 0.1//là tỉ trọng, mặc định là 0, nếu có fixture thì sẽ cộng dồn thêm khối lượng các Fixture bên trong, nếu các
                 //fixture k bên trong k đc set khối lượng sẽ mặc định là 1kg. Set là số > 0 là đc

        //BoxCollider là 1 component khiến cho 1 component trở thành body vật lý.
        //Nó khiến cho vị trí của entity bao ngoài đó bị ảnh hưởng bởi World
        //Ta set width và height của nó trùng với width và height của vật thể để làm toàn bộ vật thể thay đổi theo box1
        //và box 1 bị ảnh hưởng bởi thế giới vật lý. Ở đây ta set có 1 nửa chỉ phần có Collider mới bị ảnh hưởng bởi World
        fixture.onBeginContact: {
            collisionSound.play()
            collisionParticleEffect.start()
            //hàm start của Particle sẽ chạy hiệu ứng đã set X stop là dừng ngay lập tức
            //Nếu autoStart là true thì sẽ tự chạy lúc startup, k cần gọi start còn nếu duration set là
            //ParticleBase.Infinite, nó sẽ chỉ chạy 1 lần, các lần start sau sẽ k hoạt động
        }
        //fixture là cái cho phép truy cập vào box shape, 1 alias property tức mỗi BoxCollider có 1 biến
        //kiểu Fixture bên trong Box2D. Ta có thể lấy nó check va chạm như này
    }
    SoundEffect {
        id: collisionSound
        source: "../../assets/snd/boxCollision.wav"
    }
    Particle {
        id: collisionParticleEffect
        positionType: ParticleBase.Free//là ParticleBase.Free tức là move theo cha song song bth
        fileName: "../../assets/particle/SmokeParticle.json"
        //fileName là file JSON chứa các thuộc tính luôn, ta có thể viết các thuộc tính chay ở đây cx đc, nó
        //sẽ đè lên các thú trong file JSON

        //JSON sẽ có 1 object có tên bất kỳ, các thuộc tính object đó chính là của particle muốn set. Ta nên để kiểu
        //JSON là tái sử dụng Particle
        //angleVariance-phương sai góc-> nó sẽ loe ra khỏi góc đó 1 tí chứ kp mãi ở 1 góc
        //blendFuncSource, blendFuncDestination là 2 thuộc tính xử lý blend ở phiên bản cũ. Bh nó đã mặc định
        //source là 1 và destination là 771 với mọi Particle để có hiệu ứng chuẩn rồi, tuy nhiên thích thì
        //ta chỉnh nếu muôn -> để mặc định
        //emitterType có 2 loại là gravity và radius, mỗi loại có các thuộc tính riêng
        //gravity là 1 điểm mặc định là 0,0. Trong qml dùng là QPointF(,) với x là góc xoay, y là g của trọng lực
        //finishColor là màu cuối sẽ chuyển dần sang, alpha cũng là kênh màu chuyển sang
        //maxParticles số lượng particle tạo ra trong suốt particleLifespan
        //maxRadius chỉ có trong type radius là kích thước ending
        //particleLifespan thời gian sống của mỗi particle
        //positionType vị trí của các particle đã đc emit khi cái item có nó di chuyển or xoay
        //radialAcceleration gia tốc xoay, chỉ có tác dụng trong type radius
        //sourcePositionVariance vị trí của emitter ban đầu bị lệch đi bao nhiêu theo 2 trục
        //speed tốc độ chỉ có tác dụng trong type gravity
        //tangentialAcceleration gia tốc tiếp tuyến trong gravity
        //finishColorAlpha thì alpha là độ transparent
        //textureFileName là image texture cho 1 single particle
    }
    //Particle là component dùng các hiệu ứng lửa, khói, nổ, mưa xảy ra trong 1 khoảng thời gian đó
    //Trong felgo, ta có thể edit particle với demo Particle rồi xuất nó ra file json theo ý thích
    //=>sẽ lưu ở  C:\Users\Admin\Documents\Felgo Live Client\particles
    //để dùng 1 kiểu khác, vô file EntityPropertiesMenu.qml và sửa dòng 19 currentEditableType
    //thành đầu file json cần dùng trong C:\Users\Admin\Documents\Felgo Live Client\particles
    //nếu muốn dùng 1 texture do ta tự tạo có thể tạo ra 1 file json khác or sửa textureFileName
    //của file json đó đi
    //toàn tập sử dụng ở https://felgo.com/doc/felgo-demos-particleeditor-example/
}
