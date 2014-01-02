/// <reference path="jquery-2.0.3.js" />
var ui = (function () {

    function buildLoginField() {
        return '<div id="forms">\
                <h1>FasonTefter Gallery</h1>\
            <ul class="nav nav-tabs">\
                <li><a href="#login" data-toggle="tab">Log in</a></li>\
                <li><a href="#register" data-toggle="tab">Register</a></li>\
                <li id="error-field"></li>\
            </ul>\
            <div class="tab-content">\
            <div class="tab-pane fade active in" id="login">\
                <label for="tb-login-username">Username: </label>\
                <input type="text" id="tb-login-username" data-toggle="tooltip" title="at least 4 characters" />\
                <label for="tb-login-password">Password: </label>\
                <input type="text" id="tb-login-password" />\
                <button class="btn" id="btn-login">login</button>\
            </div>\
            <div class="tab-pane fade" id="register">\
                <label for="tb-register-username">Username: </label>\
                <input type="text" id="tb-register-username" />\
                <label for="tb-register-first-name">First Name: </label>\
                <input type="text" id="tb-register-first-name" />\
                <label for="tb-register-last-name">Last Name: </label>\
                <input type="text" id="tb-register-last-name" />\
                <label for="tb-register-password">Password: </label>\
                <input type="text" id="tb-register-password" />\
                <button class="btn" id="btn-register">Register</button>\
            </div>\
            </div>\
        </div>';
    };

    function buildGameContainer(nickname) {
        return '<span id="login-info"><span id="user-nickname">Hello, ' + $("<div />").html(nickname).text() + '!</span>\
                <button class="btn" id="btn-logout">Logout</button></span>\
                <div id="create-game-holder">\
                <label for="tb-create-title">New game title:</label> <input type="text" id="tb-create-title"/>\
                <button id="btn-create-game">Create game</button></div>\
                <div id="error-field"></div>\
                <div id="open-games-wrapper"><h2>Open</h2>\
                <div id="open-games-container"></div></div>\
                <div id="active-games-wrapper"><h2>Active</h2>\
                <div id="active-games-container"></div></div>\
                <div id="game-field"></div>\
                <div id="game-holder">\
		        </div>\
                <div id="messages-wrapper"><h2>Messages</h2>\
                <div id="messages-holder">\
                </div></div>\
                <div id="scoreboard-wrapper"><h2>Scoreboard</h2>\
                <div id="scores-holder">\
                </div> </div>';
    }

    function buildOpenGames(games) {
        var list = '<ul>';

        for (var i = 0; i < games.length; i++) {
            var game = games[i];

            list += '<li data-game-id="' + $("<div />").html(game.id).text() + '">' + '<span>' + $("<div />").html(game.title).text() + '</span>' +
                "<span> created by " + $("<div />").html(game.creator).text() + '</span><button class="btn-join-game">Join game</button></li>';
        }

        list += "</ul>";

        return list;
    }

    function buildActiveGames(games, nickname) {
        var list = '<ul>';

        for (var i = 0; i < games.length; i++) {
            var game = games[i];

            list += '<li data-game-id="' + $("<div />").html(game.id).text() + '">' + '<span>' + $("<div />").html(game.title).text() + '</span>' +
                "<span> created by " + $("<div />").html(game.creator).text() + '</span>';
            if (game.status == "in-progress") {
                list += '<button class="btn-expand-game">Expand game</button>';
            } else if (game.status == 'full' && game.creator == nickname) {
                list += '<button class="btn-start-game">Start game</button>';
            }

            list += '</li>';
        }

        list += "</ul>";
        return list;
    }

    function buildMessages(messages) {
        var list = '<ul class="messages">';

        for (var i = 0; i < messages.length; i++) {

            var message = messages[i];

            list += '<li class="' + $("<div />").html(message.type).text() + '">' + $("<div />").html(message.text).text() + '</li>';
        }

        list += '</ul>';
        return list;
    }

    function buildScoresField(scoresObjects) {
        var list = '<ul class="scores-list">';

        for (var i = 0; i < scoresObjects.length; i++) {
            var currentObject = scoresObjects[i];

            list += '<li>Nickname: ' + $("<div />").html(currentObject.nickname).text() +
                ', Score: ' + $("<div />").html(currentObject.score).text() + ' points</li>';
        }
        list += '</ul>';
        return list;
    }

    function appendHeroes(owner) {

        for (var i = 0; i < owner.units.length; i++) {

            var unit = owner.units[i];

            var currentRow = unit.position.x;
            var currentColl = unit.position.y;

            var square = '<a href="#" class="hero" data-unit-id="' + $("<div />").html(unit.id).text() + '">';
            square += '<div class="characteristics">type: ' + $("<div />").html(unit.type).text() + '</div>';
            square += '<div class="characteristics">att: ' + $("<div />").html(unit.attack).text() + '</div>';
            square += '<div class="characteristics">def: ' + $("<div />").html(unit.armor).text() + '</div>';
            square += '<div class="characteristics">health: ' + $("<div />").html(unit.hitPoints).text() + '</div>';
            suqare = "</a>";

            var element = $('#row' + currentColl + ' #coll' + currentRow);

            element.html(square);
            element.css("background", unit.owner);
            element.css('color', '#fff');
        }
    }

    function buildGameField(game) {
        var html = '<table border="1" cellspacing="5" cellpadding="5" data-game-id="' + $("<div />").html(game.gameId).text() + '">\
        <tr>\
            <th id="game-title">' + $("<div />").html(game.title).text() + '</th>\
        </tr>\
        <tr>\
            <th class="player">' + $("<div />").html(game.red.nickname).text() + '</th>\
            <th class="player">' + $("<div />").html(game.blue.nickname).text() + '</th>\
        </tr>';

        for (var i = 0; i < 9; i++) {
            html += '<tr id="row' + i + '" data-row="' + i + '">';

            for (var j = 0; j < 9; j++) {
                html += '<td id="coll' + j + '" data-coll="' + j + '">';

                html += '</td>';
            }

            html += '</tr>';
        }

        return html;
    }

    function buildGalleryUI(users) {
        var html = '<header><div class="navbar">\
  <div class="navbar-inner">\
    <div class="container">';
        html += '<a class="btn btn-navbar" data-toggle="collapse" data-target=".nav-collapse">\
          <span class="icon-bar"></span>\
          <span class="icon-bar"></span>\
          <span class="icon-bar"></span></a>';
        html += '<a class="brand" id="usernameField" href="#">' + localStorage.getItem("username") + '</a>';
//        html += '<a class="btn btn-navbar" data-toggle="collapse" data-target=".nav-collapse">\
//          <span class="icon-bar"></span>\
//          <span class="icon-bar"></span>\
//          <span class="icon-bar"></span></a>\
//';
        //html += '<li class="divider-vertical"></li>';
        var usersLength = users.length;
        html += '<div class="nav-collapse collapse navbar-responsive-collapse"><ul class="nav"><li><a href="#" id="btn-logout">log out</a></li><li class="dropdown"><a href="#" class="dropdown-toggle" data-toggle="dropdown">People<b class="caret"></b></a><ul class="dropdown-menu">';

        for (var i = 0; i < usersLength; i++) {
            html += '<li><a href="#" data-username="' + users[i].username + '" class="person">' + users[i].firstName + " " + users[i].lastName + "</a></li>";
        }
        html += "</ul>";
        html+= "</li>";
        //html += '<li class="divider-vertical"></li>';
        html += '<input type="text" class="search-query span2" placeholder="folder name" id="folderName">';
        html += '<li><a href="#" id="btn-createFolder">create folder</a></li></ul>';
        html += '<ul class="nav pull-right"><li class="dropdown"><a href="#" clas="dropdown-toggle" data-toggle="dropdown">\
            upload<b class="caret"></b></a><ul class="dropdown-menu"><li><button id="save" >Download</button></li><li><button id="uploadToDropbox">Upload to Dropbox </button></li></ul>'
        html += '</div></div></div></div></header>';

        return html;
    }

    //function generateTreeViewAlbums(albums, html) {
    //    var count = albums.lenght;
    //    html += '<li data-expanded="false">' + albums.title;

    //    for (var i = 0; i < count; i++) {
    //        generateTreeViewAlbums(albums[i], html);
    //    }


    //    html += '</li>';
    //}

    function buildTreeViewUI(gallery) {

        if (!gallery) {
            return;
        }

        var html = '<ul id="menu" class="ui-menu ui-widget ui-widget-content ui-corner-all" role="menu" tabindex="0">';
        var albumsLength = gallery.albums.length;

        var albums = gallery.albums;

        for (var i = 0; i < albumsLength; i++) {
            html += '<li class="ui-menu-item" role="presentation">';
            html += '<a href="#" class="ui-corner-all folder" tabindex="-1" role="menuitem" data-album-id="' +
                albums[i].ID + '">' + albums[i].Title + '</a>';
            html += "</li>";
        }

        //var imagesLength = gallery.images.length;
        //var images = gallery.images;

        //for (var i = 0; i < imagesLength; i++) {
        //    html += '<li class="ui-menu-item" role="presentation">';
        //    html += '<a href="#" class="image" data-image-id="' + images[i].ID + '">' + images[i].Title + "</a>";
        //    html += "</li>"
        //}

        //html += "</ul></li>";
        html += "</ul>";
        html += "<div id='imageHolder'></div>";
        return html;
    }


    return {
        getLoginField: buildLoginField,
        getGalleryUI: buildGalleryUI,
        getTreeViewUI: buildTreeViewUI,

        getGameContainer: buildGameContainer,
        getOpenGames: buildOpenGames,
        getActiveGames: buildActiveGames,
        getScores: buildScoresField,
        getGameField: buildGameField,
        getHeroes: appendHeroes,
        getMessages: buildMessages,
    }
})();

