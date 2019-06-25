		function sleep(ms) {
		
			return new Promise(resolve => setTimeout(resolve, ms));
		}
		
		async function sendRequest(url, elem, message){
		
		var request = new XMLHttpRequest();
		
		request.open("GET",url,true);
		request.send();

		document.getElementById(elem).innerHTML = message;
		await sleep(3000);
		document.getElementById(elem).innerHTML = "";
		}

		async function loadVideoPage(){
			
			window.location.href = "video.html";
			
			var loadVideoPage_request = new XMLHttpRequest();
			
			loadVideoPage_request.open("GET","http://10.5.5.9/gp/gpControl/command/mode?p=0",true);
			loadVideoPage_request.send();
			await sleep(500);
			loadVideoPage_request.open("GET","http://10.5.5.9/gp/gpControl/command/sub_mode?mode=0&sub_mode=0",true);
			loadVideoPage_request.send();
		}
		
		async function loadPhotoPage(){
		
			window.location.href = "photo.html";
			
			var loadPhotoPage_request = new XMLHttpRequest();
			
			loadPhotoPage_request.open("GET","http://10.5.5.9/gp/gpControl/command/mode?p=1",true);
			loadPhotoPage_request.send();
			await sleep(500);
			loadPhotoPage_request.open("GET","http://10.5.5.9/gp/gpControl/command/sub_mode?mode=1&sub_mode=0",true);
			loadPhotoPage_request.send();
		}
		
		async function loadMultiShotPage(){
			
			window.location.href = "multishot.html";
					
			var loadMultiShotPage_request = new XMLHttpRequest();
			
			loadMultiShotPage_request.open("GET","http://10.5.5.9/gp/gpControl/command/mode?p=2",true);
			loadMultiShotPage_request.send();
			await sleep(500);
			loadMultiShotPage_request.open("GET","http://10.5.5.9/gp/gpControl/command/sub_mode?mode=2&sub_mode=0",true);
			loadMultiShotPage_request.send();
		}
		
		async function loadSurveyPage(){
			
			window.location.href = "survey.html";
			
			var loadSurveyPage_request = new XMLHttpRequest();
			
			loadSurveyPage_request.open("GET","http://10.5.5.9/gp/gpControl/command/mode?p=1",true);
			loadSurveyPage_request.send();
			await sleep(500);
			loadSurveyPage_request.open("GET","http://10.5.5.9/gp/gpControl/command/sub_mode?mode=1&sub_mode=0",true);
			loadSurveyPage_request.send();
			await sleep(500);
			loadSurveyPage_request.open("GET","http://10.5.5.9/gp/gpControl/setting/17/0",true);
			loadSurveyPage_request.send();
		}