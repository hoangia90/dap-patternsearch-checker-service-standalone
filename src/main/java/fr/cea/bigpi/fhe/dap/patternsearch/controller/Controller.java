package fr.cea.bigpi.fhe.dap.patternsearch.controller;

import java.util.List;

//import java.util.ArrayList;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.multipart.MultipartFile;

import fr.cea.bigpi.fhe.dap.patternsearch.model.analyticRequestPayload.AnalyticRequestPayload;
import fr.cea.bigpi.fhe.dap.patternsearch.model.analyticRequestPayload.IaiResponse;
//import fr.cea.bigpi.fhe.dap.patternsearch.model.FHEFileSystem;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import io.swagger.annotations.ApiResponse;
import io.swagger.annotations.ApiResponses;

@RequestMapping("/openapi/v1")
public interface Controller {

	final Logger logger = LoggerFactory.getLogger(Controller.class.getName());

//	@ApiOperation(value = "Upload Encrypted File (.ct)", notes = "This method uploads an encrypted file and return the requestID number", nickname = "uploadEncryptedFile", response = String.class, authorizations = {}, tags = {
//			"Generic - Analysis With Data Management", })
//	@ApiResponses(value = { @ApiResponse(code = 200, message = "Server response", response = String.class),
//			@ApiResponse(code = 400, message = "Bad request", response = String.class),
//			@ApiResponse(code = 401, message = "Unauthorized", response = String.class),
//			@ApiResponse(code = 404, message = "Not found", response = String.class),
//			@ApiResponse(code = 500, message = "Error for HTTPS call trustAnchors", response = String.class) })
//	@PostMapping("/analysis/01-uploadEncryptedFile")
//	public @ResponseBody ResponseEntity<String> uploadEncryptedFile(
//			@ApiParam(name = "file", value = "", example = "", required = true) @RequestParam("file") MultipartFile file,
//			@ApiParam(name = "partnerID", value = "", example = "", required = true) @RequestParam("partnerID") String partnerID);

//	@ApiOperation(value = "Check If An Uploaded Encrypted File's Information Is In Database (SQL)", notes = "This method checks if an uploaded encrypted file's information exists in database and returns an encrypted .ct file result (or a zip file for multiple encrypted .ct files). The file result is decrypted with 04-decryptCheckedResult at client micro-service. Note that: the requestID number is used in this method generated from the 01-uploadFile", nickname = "checkWithEncryptedFile", response = ResponseEntity.class, authorizations = {}, tags = {
//			"Generic - Analysis With Data Management", })
//	@ApiResponses(value = { @ApiResponse(code = 200, message = "Server response", response = String.class),
//			@ApiResponse(code = 400, message = "Bad request", response = String.class),
//			@ApiResponse(code = 401, message = "Unauthorized", response = String.class),
//			@ApiResponse(code = 404, message = "Not found", response = String.class),
//			@ApiResponse(code = 500, message = "Error for HTTPS call trustAnchors", response = String.class) })
//	@PostMapping("/analysis/02-checkWithEncryptedFile")
//	public @ResponseBody ResponseEntity<byte[]> checkWithEncryptedFile(
//			@ApiParam(name = "partnerID", value = "", example = "", required = true) @RequestParam("partnerID") String partnerID,
//			@ApiParam(name = "requestID", value = "", example = "", required = true) @RequestParam("requestID") String requestID);

	//
//	@ApiOperation(value = "Check If An Uploaded Encrypted File's Information Is In A Given Local Data List", notes = "This method checks if an uploaded encrypted file's information exists in a given data list and returns an encrypted .ct file result (or a zip file for multiple encrypted .ct files). The file result is decrypted with 04-decryptCheckedResult at client micro-service. Note that: the requestID number is used in this method generated from the 01-uploadFile", nickname = "checkUploadedEncryptedFileWDataList", response = ResponseEntity.class, authorizations = {}, tags = {
//			"Generic - Analysis With Data Management", })
//	@ApiResponses(value = { @ApiResponse(code = 200, message = "Server response", response = String.class),
//			@ApiResponse(code = 400, message = "Bad request", response = String.class),
//			@ApiResponse(code = 401, message = "Unauthorized", response = String.class),
//			@ApiResponse(code = 404, message = "Not found", response = String.class),
//			@ApiResponse(code = 500, message = "Error for HTTPS call trustAnchors", response = String.class) })
//	@PostMapping("/analysis/02-checkEncryptedFileWList")
//	public @ResponseBody ResponseEntity<byte[]> checkEncryptedFileWList(
//			@ApiParam(name = "partnerID", value = "", example = "", required = true) @RequestParam("partnerID") String partnerID,
//			@ApiParam(name = "requestID", value = "", example = "", required = true) @RequestParam("requestID") String requestID,
//			@ApiParam(name = "dataList", value = "", example = "", required = true) @RequestParam("dataList") List<String> dataList);

//	@ApiOperation(value = "Download Encrpted File", notes = "This method download an encrpted file", nickname = "downloadEncrptedFile", response = ResponseEntity.class, authorizations = {}, tags = {
//			"Generic - Analysis With Data Management", })
//	@ApiResponses(value = { @ApiResponse(code = 200, message = "Server response"),
//			@ApiResponse(code = 400, message = "Bad request", response = String.class),
//			@ApiResponse(code = 401, message = "Unauthorized", response = String.class),
//			@ApiResponse(code = 404, message = "Not found", response = String.class),
//			@ApiResponse(code = 500, message = "Error for HTTPS call trustAnchors", response = String.class) })
//	@PostMapping("/analysis/downloadEncryptedFile")
//	public ResponseEntity<byte[]> downloadEncryptedFile(
//			@ApiParam(name = "Id", value = "", example = "", required = true) @RequestParam(name = "Id") Integer Id,
//			@ApiParam(name = "partnerID", value = "", example = "", required = true) @RequestParam("partnerID") String partnerID);

//	@ApiResponses(value = { @ApiResponse(code = 200, message = "Server response", response = String.class),
//			@ApiResponse(code = 400, message = "Bad request", response = String.class),
//			@ApiResponse(code = 401, message = "Unauthorized", response = String.class),
//			@ApiResponse(code = 404, message = "Not found", response = String.class),
//			@ApiResponse(code = 500, message = "Error for HTTPS call trustAnchors", response = String.class) })
//	@PostMapping("/analysis/checkEncryptedFileWDataList-Auto")
//	@ApiOperation(value = "Check an encrypted file with a list of encrypted file", notes = "This method checks if an encrypted file's information is stored in a give data list and then returns an result", tags = {
//			"Generic - Analysis", })
//	public ResponseEntity<byte[]> checkEncryptedFileWDataListAuto(
//			@ApiParam(name = "file2bchecked", value = "Any Character", example = "", required = true) @RequestParam("file2bchecked") String file2bchecked,
//			@ApiParam(name = "partnerID", value = "", example = "", required = true) @RequestParam("partnerID") String partnerID,
//			@ApiParam(name = "dataList", value = "", example = "", required = true) @RequestParam("dataList") List<String> dataList);

	// E-Corridor Part - Begin
	@ApiResponses(value = { @ApiResponse(code = 200, message = "Server response", response = String.class),
			@ApiResponse(code = 400, message = "Bad request", response = String.class),
			@ApiResponse(code = 401, message = "Unauthorized", response = String.class),
			@ApiResponse(code = 404, message = "Not found", response = String.class),
			@ApiResponse(code = 500, message = "Error for HTTPS call trustAnchors", response = String.class) })
//	@PostMapping(value = "/analysis/checkEncryptedFileWDataList-Base64", consumes = {
//			"application/json;charset=UTF-8" })
//	@ApiOperation(value = "checkEncryptedFileWDataList", notes = "Used for E-Corridor project, receives a predefined payload with ", tags = { "E-Corridor - Analysis", })
//	public ResponseEntity<String> checkEncryptedFileWDataListAutoBase64(
//			@RequestBody AnalyticRequestPayload analyticRequestPayload);
	@PostMapping(value = "/analysis/startAnalytics", consumes = { "application/json;charset=UTF-8" })
	@ApiOperation(value = "startAnalytics", notes = "Used for E-Corridor project, receives a predefined payload with ", tags = {
			"E-Corridor - Analysis", })
	public ResponseEntity<String> startAnalytics(@RequestBody AnalyticRequestPayload analyticRequestPayload);

	@ApiResponses(value = { @ApiResponse(code = 200, message = "Server response", response = String.class),
			@ApiResponse(code = 400, message = "Bad request", response = String.class),
			@ApiResponse(code = 401, message = "Unauthorized", response = String.class),
			@ApiResponse(code = 404, message = "Not found", response = String.class),
			@ApiResponse(code = 500, message = "Error for HTTPS call trustAnchors", response = String.class) })
	@PostMapping(value = "/analysis/stopAnalytics")
	@ApiOperation(value = "stopAnalytics", notes = "", tags = { "E-Corridor - Analysis", })
	public @ResponseBody ResponseEntity<String> stopAnalytics(
			@ApiParam(name = "partnerID", value = "Used for stopping the running analysis", example = "", required = true) @RequestParam("partnerID") String partnerID);

	@ApiResponses(value = { @ApiResponse(code = 200, message = "Server response", response = String.class),
			@ApiResponse(code = 400, message = "Bad request", response = String.class),
			@ApiResponse(code = 401, message = "Unauthorized", response = String.class),
			@ApiResponse(code = 404, message = "Not found", response = String.class),
			@ApiResponse(code = 500, message = "Error for HTTPS call trustAnchors", response = String.class) })
	@PostMapping(value = "/analysis/receiveAnalyticsResult")
	@ApiOperation(value = "receiveAnalyticsResult", notes = "Used as the on_finish_url and receives result from checkEncryptedFileWDataList-Base64 api", tags = {
			"E-Corridor - Analysis", })
	public @ResponseBody ResponseEntity<String> receiveAnalyticsResult(@RequestBody IaiResponse iaiResponse);
	// E-Corridor Part - End

//	@ApiOperation(value = "Concate Checked Result Files", notes = "This method concates multiple checked result files", nickname = "concateCheckedResultFiles", response = ResponseEntity.class, authorizations = {}, tags = {
//			"Driving License For Distributed Computing", })
//	@ApiResponses(value = { @ApiResponse(code = 200, message = "Server response"),
//			@ApiResponse(code = 400, message = "Bad request", response = String.class),
//			@ApiResponse(code = 401, message = "Unauthorized", response = String.class),
//			@ApiResponse(code = 404, message = "Not found", response = String.class),
//			@ApiResponse(code = 500, message = "Error for HTTPS call trustAnchors", response = String.class) })
//	@PostMapping("/analysis/drivingLicense/concateCheckedResultFiles")
//	public ResponseEntity<FHEFileSystem> concateFiles(
//			@ApiParam(name = "file1", value = "", example = "", required = true) @RequestParam("file1") FHEFileSystem file1,
//			@ApiParam(name = "file2", value = "", example = "", required = true) @RequestParam("file2") FHEFileSystem file2,
//			@ApiParam(name = "filename", value = "", example = "", required = true) @RequestParam("filename") String filename);

//	@ApiOperation(value = "Check If An Uploaded Encrypted Driving License Number Is In A List", notes = "This method checks if an uploaded encrypted driving license number exists in the given list. The file result is decrypted with 04-decryptCheckedResult", nickname = "checkByFilewList", response = ResponseEntity.class, authorizations = {}, tags = {
//			"Driving License For Distributed Computing", })
//	@ApiResponses(value = { @ApiResponse(code = 200, message = "Server response", response = String.class),
//			@ApiResponse(code = 400, message = "Bad request", response = String.class),
//			@ApiResponse(code = 401, message = "Unauthorized", response = String.class),
//			@ApiResponse(code = 404, message = "Not found", response = String.class),
//			@ApiResponse(code = 500, message = "Error for HTTPS call trustAnchors", response = String.class) })
//	@PostMapping("/analysis/drivingLicense/checkByFilewList")
//	public @ResponseBody ResponseEntity<byte[]> drivingLicenseCheckByFilewList(
//			@ApiParam(name = "partnerID", value = "", example = "", required = true) @RequestParam("partnerID") String partnerID,
//			@ApiParam(name = "requestID", value = "", example = "", required = true) @RequestParam("requestID") String requestID,
//			@ApiParam(name = "files", value = "", example = "", required = true) @RequestParam("files") ArrayList<String> files);

}
