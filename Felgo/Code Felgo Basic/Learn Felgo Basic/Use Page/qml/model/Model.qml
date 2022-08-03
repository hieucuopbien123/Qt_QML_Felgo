import QtQuick 2.0
import Felgo 3.0

Item {
    id: item
    property alias dispatcher: connection.target
    signal end()
    Client{
        id: client
    }

    Connections{
        id: connection
        onOpenContent:{
            end()
        }
        onGetVoice:{
            console.log("!")
            client.getVoice(function(){
                console.log("Callback calling")
            })
        }
    }
}
