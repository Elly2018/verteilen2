const PageType  = Object.freeze({
    HOMEPAGE: 0,
    SETTING: 1,
    LOG: 2,
    TERMINAL: 3
});

let page = PageType.HOMEPAGE;

function close_configuration() {
    document.getElementById('config-dropdown').removeAttribute('open');
}

const ws = new WebSocket("ws://" + window.location.host + "/ws");

ws.onopen((ev) => {

})

ws.onclose(ev => {
    
})

ws.onmessage = (event) => {
    try {
        const jsonObject = JSON.parse(event.data);
        console.log(jsonObject);
        if(jsonObject["type"] == "init_log"){

        }
    } catch (error) {
        console.error("Failed to parse string as JSON:", error);
    }
}

ws.onerror((ev) => {

})