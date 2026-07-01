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