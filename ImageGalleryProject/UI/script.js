var zoom = $("#zoom");
var createFolder = $("#CreateFolder");
var img = $(".content>img");
var folderID =1;
var currentId;
Zoom();
CreateFolder();


function Zoom() {


	img.click(function(event) {
		var x = $(this).attr('src');
		zoom.html("<img src ='" + x + "'>")
	});
	zoom.click(function(event) {
		var x = $(this).attr('src');
		zoom.html("");

	});
}

$("#AddFolder").click(function(event) {

	createFolder.css('display', 'inline-block');
	$("#FolderName").css('display', 'inline-block');

});

function CreateFolder() {
	createFolder.click(function(event) {
		var z = $("#FolderName").val();
		$(".content").append("<div class='folder' id='"+folderID+"'><img src='folder.png'>"+z+"</div>")
		folderID++;
	});
}


function OpenFolder(){
$("#app").delegate('.folder', 'click', function(event) {
	$(".content img ").addClass('hidden');
	
	currentId = $(this).attr('id');
//	$("#"+currentId).append("<div><img src='1.jpg'><a name ='"+currentId+"'></a> </div>")
	$("#menu").append("<li><a href='#"+currentId+"' >" + currentId +"</a></li>")
});
//		
}
function AddImage() {
	$("#AddImage").click(function(event) {
		$("#"+currentId).append("<div><img src='1.jpg'><a name ='"+currentId+"'></a> </div>")

	});
	
}
OpenFolder();
AddImage();