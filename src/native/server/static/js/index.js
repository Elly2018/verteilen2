const PageType  = Object.freeze({
    HOMEPAGE: 0,
    SETTING: 1,
    LOG: 2,
    TERMINAL: 3
});

let page = PageType.HOMEPAGE;
const logs = [];

function close_resource() {
    document.getElementById('resource-dropdown').removeAttribute('open');
}

function close_configuration() {
    document.getElementById('config-dropdown').removeAttribute('open');
}

const ws = new WebSocket("ws://" + window.location.host + "/ws");

ws.onopen = (ev) => {
    console.log("[web] websocket connection successfully established.");
}

ws.onclose = (ev) => {
    console.log("[web] websocket connection successfully closed.");
}

ws.onmessage = (event) => {
    try {
        const jsonObject = JSON.parse(event.data);
        console.log(jsonObject);
        if(jsonObject["type"] == "add_log"){
            htmx.trigger("#viewer-content-button", "refresh-viewer");
        }
    } catch (error) {
        console.error("[web] failed to parse string as JSON:", error);
    }
}

ws.onerror = (ev) => {
    console.error("[web] websocket connection error ocurred: ", ev);
}

setInterval(() => {
    const value = cookieStore.get('key');
    if(value != undefined && ws.readyState == WebSocket.OPEN) {
        ws.send(JSON.stringify({
            key: value
        }))
    }
}, 1000);