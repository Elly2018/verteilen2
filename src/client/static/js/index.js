const PageType  = Object.freeze({
    HOMEPAGE: 0,
    SETTING: 1,
    LOG: 2,
    TERMINAL: 3
});

let page = PageType.HOMEPAGE;
const logs = [];

function close_configuration() {
    document.getElementById('config-dropdown').removeAttribute('open');
}

document.addEventListener("DOMContentLoaded", () => {
    update_viewer();
})

function update_viewer() {
    console.log("update_viewer");
    const ctx = document.getElementById('viewer-content');
    if(ctx == null) return;
    ctx.innerText = JSON.stringify(logs);
}

const ws = new WebSocket("ws://" + window.location.host + "/ws");

ws.onopen = (ev) => {

}

ws.onclose = (ev) => {
    
}

ws.onmessage = (event) => {
    try {
        const jsonObject = JSON.parse(event.data);
        console.log(jsonObject);
        if(jsonObject["type"] == "init_log"){
            jsonObject["data"].forEach(element => {
                logs.push(element)
            });
            update_viewer();
        }
    } catch (error) {
        console.error("Failed to parse string as JSON:", error);
    }
}

ws.onerror = (ev) => {
    
}