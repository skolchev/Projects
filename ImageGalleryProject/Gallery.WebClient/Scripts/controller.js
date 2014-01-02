/// <reference path="class.js" />
/// <reference path="jquery-2.0.3.js" />
/// <reference path="persister.js" />
/// <reference path="ui.js" />

var controllers = (function () {
    var rootUrl = "http://teamdexterapp.apphb.com/api/";
	var Controller = Class.create({
		init: function () {
			this.persister =  persister.get(rootUrl);
		},
		loadUI: function (selector) {
			if (this.persister.isUserLoggedIn()) {
				this.loadGalleryUI(selector);
			}
			else {
				this.loadLoginFormUI(selector);
			}
			this.attachUIEventHandlers(selector);
		},
		loadLoginFormUI: function (selector) {
		    var loginFormHtml = ui.getLoginField();
			$(selector).html(loginFormHtml);
		},
		loadGalleryUI: function (selector) {
		    this.persister.user.getAll(function (users) {
		        var html = ui.getGalleryUI(users);
		        $(selector).hide(); // CAUSES ISSUES
		        $(selector).html(html);
		        $(selector).fadeIn(700);
		    });
		},
		loadGallery: function (selector, gallery){
		    $("#menu").remove();
		    var html = ui.getTreeViewUI(gallery);
		    $(selector).append(html);
		},
		//loadGame: function (selector, gameId) {
		//	this.persister.game.state(gameId, function (gameState) {
		//		var gameHtml = ui.gameState(gameState);
		//		$(selector + " #game-holder").html(gameHtml)
		//	});
		//},
		attachUIEventHandlers: function (selector) {
			var wrapper = $(selector);
			var self = this;

			wrapper.on("click", "#btn-login", function () {
				var user = {
					username: $(selector + " #tb-login-username").val(),
					password: $(selector + " #tb-login-password").val()
				}

				self.persister.user.login(user, function () {
				    $("#forms").fadeOut(700);
				    console.log("passed");

				    self.loadGalleryUI(selector);
				}, function () {
					wrapper.html("oh no..");
				});
				return false;
			});
			wrapper.on("click", "#btn-register", function () {
			    var user = {
			        username: $(selector + " #tb-register-username").val(),
			        password: $(selector + " #tb-register-password").val(),
			        firstName: $(selector + " #tb-register-first-name").val(),
			        lastName: $(selector + " #tb-register-last-name").val()
			    };
			    self.persister.user.register(
                    user,
                    function (data) {
                        $("#forms").hide("highlight", {}, 1000);
                        self.loadGalleryUI(selector);
                    },
                    function (error) {
                        var errorObject = JSON.parse();
                        $("#error-field").html(errorObject.Message);
                    }
                );
			});
			wrapper.on("click", "#btn-logout", function () {
				self.persister.user.logout(function () {
					self.loadLoginFormUI(selector);
				});
			});

			wrapper.on("click", ".person", function (ev) {
			    debugger;
			    var username = $(ev.target).attr("data-username");
			    self.persister.gallery.getSingle(
                    username,
                    function (data) {
                        var gallery = data;
                        self.loadGallery(selector, gallery);
                    },
                    function (errorData) {
                    });
			});

			wrapper.on("click", "#usernameField", function (ev) {
			    var username = $(ev.target).text();
			    self.persister.gallery.getSingle(
                          username,
                          function (data) {
                              console.log(data);
                              var gallery = data;
                              self.loadGallery(selector, gallery);
                          },
                          function (errorData) {
                          });
			});

			wrapper.on("click", "#btn-createFolder", function (ev) {
			    var folderName = $("#folderName").val();
			    self.persister.album.create(folderName, function (data) {
			        alert("success");
			    }, function (error) { });

			})

			wrapper.on("click", ".image", function (ev) {
			    var imageID = $(ev.target).attr("data-image-id");
			    self.persister.images.getImageByID(imageID, function (data) {
			        var image = data;
			        $(selector).appendTo("<img src='" + image.url + "'/>");
			    }, function (error) { });
			});

			wrapper.on("click", ".folder", function (ev) {
			    
			    var albumID = $(ev.target).attr("data-album-id");
			    self.persister.album.get(albumID, function (data) {
			        if (data.images.length!=0) {
			            for (var i = 0; i < data.images.length; i++) {
			                $(ev.target).append("<li class='image-url'><a href='#' data-url=" + data.images[i].url + "'>Image " + data.images[i].id + "</a></li>");
			            }

			        }
			    }, function (error) { });
			});

			wrapper.on("click", ".image-url", function (ev) {
			    var imageUrl = $(ev.target).attr("data-url");
			    var imagesId = $(ev.target).attr("data-id");
			    $("#imageHolder").html("<img src='" + imageUrl + "'/>");
			    //$("#imageHolder").html += "<div id='allComments'>";
			    //self.persister.comments.get(imagesId,function(data){
			    //    for (var i = 0; i < data.length; i++) {
			    //        $("#imageHolder").html += data[i].username;
			    //    }
			    //    $("#imageHolder").html += "</div>";
			    //},function(){});


			});

		//	<ul class="ui-menu ui-widget ui-widget-content ui-corner-all" role="menu" aria-expanded="false" style="display: none; top: 105.96875px; left: 314px;" aria-hidden="true">
		//	<li class="ui-state-disabled ui-menu-item" role="presentation" aria-disabled="true"><a href="#" id="ui-id-9" class="ui-corner-all" tabindex="-1" role="menuitem">Ada</a></li>
		//	<li class="ui-menu-item" role="presentation"><a href="#" id="ui-id-10" class="ui-corner-all" tabindex="-1" role="menuitem">Saarland</a></li>
		//	<li class="ui-menu-item" role="presentation"><a href="#" id="ui-id-11" class="ui-corner-all" tabindex="-1" role="menuitem">Salzburg</a></li>
		//</ul>

            // ===============================================================================================
			wrapper.on("click", "#open-games-container a", function () {
				$("#game-join-inputs").remove();
				var html =
					'<div id="game-join-inputs">' +
						'Number: <input type="text" id="tb-game-number"/>' +
						'Password: <input type="text" id="tb-game-pass"/>' +
						'<button id="btn-join-game">join</button>' +
					'</div>';
				$(this).after(html);
			});
			wrapper.on("click", "#btn-join-game", function () {
				var game = {
					number: $("#tb-game-number").val(),
					gameId: $(this).parents("li").first().data("game-id")
				};

				var password = $("#tb-game-pass").val();

				if (password) {
					game.password = password;
				}
				self.persister.game.join(game);
			});
			wrapper.on("click", "#btn-create-game", function () {
				var game = {
					title: $("#tb-create-title").val(),
					number: $("#tb-create-number").val(),
				}
				var password = $("#tb-create-pass").val();
				if (password) {
					game.password = password;
				}
				self.persister.game.create(game);
			});

			wrapper.on("click", ".active-games .in-progress", function () {
				self.loadGame(selector, $(this).parent().data("game-id"));
			});
		}
	});
	return {
		get: function () {
			return new Controller();
		}
	}
}());

$(function () {
	var controller = controllers.get();
	controller.loadUI("#content");
});