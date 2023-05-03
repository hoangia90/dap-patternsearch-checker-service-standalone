package fr.cea.bigpi.fhe.dap.patternsearch.service;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;
import java.util.concurrent.CompletableFuture;

import org.apache.commons.codec.binary.Base64;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.scheduling.annotation.Async;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;

import fr.cea.bigpi.fhe.dap.patternsearch.helper.Tools;
import fr.cea.bigpi.fhe.dap.patternsearch.helper.Zip;
import fr.cea.bigpi.fhe.dap.patternsearch.model.analyticRequestPayload.AnalyticRequestPayload;
import fr.cea.bigpi.fhe.dap.patternsearch.model.analyticRequestPayload.IaiResponse;

@Service
public class AnalysisServices {

	@Autowired
	FilesStorageService storageService;

	@Autowired
	private FHEPatternSearchService fhePatternSearchService;

	@Autowired
	Zip zip;

	// 4 E-Corridor Project
	@Async
	public CompletableFuture<String> startAnalysis(AnalyticRequestPayload analyticRequestPayload, String PartnerId,
			String resultName) throws InterruptedException {

		try {

			System.out.println(fhePatternSearchService.toString());

			String checkFileID = analyticRequestPayload.getIai_params().get("checkFileID");

			String checkFilePath = "";

//			System.out.println("checkFileID!!!!!!" + checkFileID.toString());

			List<String> fileInputs = new ArrayList<String>();
			if (analyticRequestPayload.getIai_files().size() == analyticRequestPayload.getIai_dpo_metadata().size()) {
				for (int i = 0; i < analyticRequestPayload.getIai_files().size(); i++) {
					String[] tokens = analyticRequestPayload.getIai_files().get(i).split("\\.(?=[^\\.]+$)");
					if (tokens[0].toString()
							.equals(analyticRequestPayload.getIai_dpo_metadata().get(i).getId().toString())) {
						System.out.println(analyticRequestPayload.getIai_datalake().toString() + "/"
								+ analyticRequestPayload.getIai_dpo_metadata().get(i).getId().toString() + "."
								+ analyticRequestPayload.getIai_dpo_metadata().get(i).getFile_extension().toString());

						Path path = Paths.get(analyticRequestPayload.getIai_datalake().toString() + "/"
								+ analyticRequestPayload.getIai_files().get(i));

						byte[] bytes = Files.readAllBytes(path);

						byte[] byteArray = Base64.decodeBase64(bytes);

						String filePath = analyticRequestPayload.getIai_datalake().toString() + "/"
								+ analyticRequestPayload.getIai_dpo_metadata().get(i).getId().toString() + "."
								+ analyticRequestPayload.getIai_dpo_metadata().get(i).getFile_extension().toString();
						BufferedOutputStream stream = new BufferedOutputStream(
								new FileOutputStream(new File(filePath)));
						stream.write(byteArray);
						stream.close();

						if (analyticRequestPayload.getIai_dpo_metadata().get(i).getId().equals(checkFileID)) {

							checkFilePath = analyticRequestPayload.getIai_datalake().toString() + "/"
									+ analyticRequestPayload.getIai_dpo_metadata().get(i).getId().toString() + "."
									+ analyticRequestPayload.getIai_dpo_metadata().get(i).getFile_extension()
											.toString();
						} else {
							fileInputs.add(analyticRequestPayload.getIai_datalake().toString() + "/"
									+ analyticRequestPayload.getIai_dpo_metadata().get(i).getId().toString() + "."
									+ analyticRequestPayload.getIai_dpo_metadata().get(i).getFile_extension()
											.toString());
						}

					} else {
						throw new Exception("Iai_files(" + i + ") id not equals Iai_dpo_metadata size(" + i + ") id");
					}
				}
			} else {
				throw new Exception("Iai_files size not equals Iai_dpo_metadata size");
			}

			String file2bchecked = checkFilePath;

			System.out.println("file2bchecked!!!!!!" + file2bchecked);

			// Set CEA as partnerID
			byte[] response = checkEncryptedFileWDataListAuto(file2bchecked, "CEA", fileInputs);
//			byte[] encoded = Base64.encodeBase64(response);
//			String path = analyticRequestPayload.getIai_datalake().toString() + "/" + resultName + ".dpo";
			String path = analyticRequestPayload.getIai_datalake().toString() + "/" + resultName + ".zip";
			
			Boolean success = false;
			String value = resultName;
			List<String> results = new ArrayList<String>();
			
			try {
//				Files.write(Paths.get(path), encoded);
				Files.write(Paths.get(path), response);
				results.add(path);
				success = true;

			} catch (IOException ex) {
				System.out.println("Could not write file, error: " + ex.toString());
				success = false;
			}

//				File f = new File(filePathString);
//				if(f.exists() && !f.isDirectory()) { 
//				    // do something
//				}

			IaiResponse iaiResponse = new IaiResponse(success, value, results);
			
			sendResultBack(analyticRequestPayload.getOn_finish_url(), iaiResponse);

//			sendByteArray(analyticRequestPayload.getOn_finish_url(), encoded);

		} catch (Exception e) {
			e.printStackTrace();
		}

		return CompletableFuture.completedFuture("Admin");
	}

	// 4 E-Corridor Project
//	public void sendByteArray(String address, byte[] byteArray) throws URISyntaxException, IOException {
//		URI url = new URI(address);
//
//		RestTemplate restTemplate = new RestTemplate();
//		ResponseEntity<String> response = restTemplate.postForEntity(url, byteArray, String.class);
//
//		System.out.println(response.getStatusCodeValue());
//		System.out.println(response.getBody());
//	}
	public void sendResultBack(String address, IaiResponse iaiResponse) throws URISyntaxException, IOException {
		URI url = new URI(address);
		System.out.println("Send result: " + iaiResponse.getSuccess() + " " + iaiResponse.getValue() + " " + iaiResponse.getResults() );
		RestTemplate restTemplate = new RestTemplate();
		ResponseEntity<String> response = restTemplate.postForEntity(url, iaiResponse, String.class);
		
//		System.out.println(response.getStatusCodeValue());
//		System.out.println(response.getBody());
	}

	public byte[] checkEncryptedFileWDataListAuto(String file2bchecked, String partnerID, List<String> dataList) {
		try {
			String requestID = UUID.randomUUID().toString();
			String filename = requestID + ".ct";
			String filePath = file2bchecked;
			byte[] bytes = Files.readAllBytes(Paths.get(filePath));
			String path = storageService.getFileDir().toString() + "/" + filename;
			Files.write(Paths.get(path), bytes);

			byte[] zipResult = checkEncryptedFileWList(partnerID, requestID, dataList);
			return zipResult;

		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}

	static <T> List<List<T>> chopped(List<T> list, final int L) {
		List<List<T>> parts = new ArrayList<List<T>>();
		final int N = list.size();
		for (int i = 0; i < N; i += L) {
			parts.add(new ArrayList<T>(list.subList(i, Math.min(N, i + L))));
		}
		return parts;
	}

	public byte[] checkEncryptedFileWList(String partnerID, String requestID, List<String> dataList) {
		int vectorSize = 102;
		// clean result
//		FHEPatternSearchService fhePatternSearchService = new FHEPatternSearchService();
		fhePatternSearchService.deleteDir(fhePatternSearchService.getResultDir() + "requestID" + ".ct");
		//
//		List<Data> allData = dataService.getAllData();
		ArrayList<String> data = new ArrayList<String>();
//		for (Data datum : allData) {
//			if (datum.getPartnerId().equals(partnerID)) {
////			data.add(datum.getContent() + fhePatternSearchService.getFilename() + ".ct");
//				data.add(datum.getContent() + datum.getDataId() + ".ct");
//			}
//		}
		data = (ArrayList<String>) dataList;
		//

		try {
//			if (data.size() > 0 && data.size() <= vectorSize) {
////				String message = "";
//				String fileName = requestID + ".ct";
//				String encryptedFilePath = storageService.getFileDir() + "/" + fileName;
//				fhePatternSearchService.checkData(encryptedFilePath, data, requestID);
//				String resultPath = fhePatternSearchService.getResultDir() + "/" + requestID + ".ct";
////			Resource resource = storageService.load(resultPath);
//				Path path = Paths.get(resultPath);
//				byte[] returnData = Files.readAllBytes(path);
//				fhePatternSearchService.deleteDir(path.toString());
//				return new ResponseEntity<byte[]>(returnData, HttpStatus.OK);
//				//
//			} else if (data.size() > 0 && data.size() > vectorSize) {

			List<List<String>> parts = chopped(data, vectorSize);
			String fileName = requestID + ".ct";
//			FilesStorageService storageService = new FilesStorageServiceImpl();
			String encryptedFilePath = storageService.getFileDir() + "/" + fileName;

			String[] resultPaths = new String[parts.size()];
			for (int i = 0; i < parts.size(); i++) {
				try {
					String outputPath = requestID + "." + (i + 1) + "." + parts.size();
					System.out.println(outputPath);
					fhePatternSearchService.checkData(encryptedFilePath, (ArrayList<String>) parts.get(i), outputPath);

//					System.out.println("bug!!!!!!!!!!here!!!!! : " + encryptedFilePath );

					resultPaths[i] = fhePatternSearchService.getResultDir() + "/" + outputPath + ".ct";
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			;

			// Check if file exist
//				boolean ready = false;
//				String strCheckPath = resultPath[(parts.size()-1)];
//				Path checkPath = Paths.get(strCheckPath);
//				while (!ready) {
//					checkPath = Paths.get(strCheckPath);
//					System.out.println(checkPath + " : " + Files.exists(checkPath));
//					if (Files.exists(checkPath)) {
//						ready = true;
//					}
//				}

			// Zip result files - start
			Tools tools = new Tools();
			boolean isDirCreated = tools.creatDir(fhePatternSearchService.getResultDir() + "/" + requestID);
//			if (isDirCreated) {

//			Zip zip = new Zip();
			String zipResultPath = zip.zipMultipleFiles(fhePatternSearchService.getResultDir() + "/" + requestID,
					requestID, resultPaths);
			// Zip result files - end

//				for (int i = 0; i < resultPaths.length; i++) {
//					fhePatternSearchService.deleteDir(resultPaths[i]);
//				}

			Path path = Paths.get(zipResultPath);
			byte[] returnData = Files.readAllBytes(path);
//				fhePatternSearchService.deleteDir(path.toString());

//			HttpHeaders responseHeaders = new HttpHeaders();
//			responseHeaders.set(HttpHeaders.CONTENT_DISPOSITION,
//					// for direct downlad "inline", for "save as" dialog "attachment" (browser
//					// dependent)
//					String.format("attachment; filename=\"" + requestID + ".zip\""));

			return returnData;

//			} else {
//				throw new Exception("Could not created the directory");
//			}
		} catch (Exception e) {
			e.printStackTrace();
		}
//		return new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
		return null;
	}

}
