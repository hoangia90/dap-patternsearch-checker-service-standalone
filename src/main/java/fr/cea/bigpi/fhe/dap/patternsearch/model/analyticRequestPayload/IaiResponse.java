package fr.cea.bigpi.fhe.dap.patternsearch.model.analyticRequestPayload;

import java.util.ArrayList;
import java.util.List;

public class IaiResponse {
	private Boolean success;
	private String value;
	private List<String> results = new ArrayList<String>();

	public IaiResponse(Boolean success, String value, List<String> results) {
		super();
		this.success = success;
		this.value = value;
		this.results = results;
	}
	
	public IaiResponse() {
	}

	// Getter Methods

	public Boolean getSuccess() {
		return success;
	}

	public String getValue() {
		return value;
	}

	// Setter Methods

	public void setSuccess(Boolean success) {
		this.success = success;
	}

	public void setValue(String value) {
		this.value = value;
	}

	public List<String> getResults() {
		return results;
	}

	public void setResults(List<String> results) {
		this.results = results;
	}
}
