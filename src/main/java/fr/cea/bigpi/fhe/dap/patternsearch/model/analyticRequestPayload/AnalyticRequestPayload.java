package fr.cea.bigpi.fhe.dap.patternsearch.model.analyticRequestPayload;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.springframework.validation.annotation.Validated;

import com.fasterxml.jackson.annotation.JsonProperty;

@Validated
public class AnalyticRequestPayload {
	@JsonProperty("session_id")
	private String session_id;
	@JsonProperty("iai_datalake")
	private String iai_datalake;
	@JsonProperty("iai_datacipher")
	private String iai_datacipher;
	@JsonProperty("iai_datakey")
	private String iai_datakey = null;
	@JsonProperty("iai_files")
	private List<String> iai_files = new ArrayList<String>();
	@JsonProperty("on_finish_url")
	private String on_finish_url;
//	IaiParams iai_params;
	@JsonProperty("iai_params")
	private Map<String, String> iai_params = new HashMap<>(); ;
	@JsonProperty("iai_dpo_metadata")
	private List<IaiMetadata> iai_dpo_metadata = new ArrayList<IaiMetadata>();

	// Getter Methods

	public String getSession_id() {
		return session_id;
	}

	public String getIai_datalake() {
		return iai_datalake;
	}

	public String getIai_datacipher() {
		return iai_datacipher;
	}

	public String getIai_datakey() {
		return iai_datakey;
	}

	public String getOn_finish_url() {
		return on_finish_url;
	}
	
	public Map<String, String> getIai_params() {
		return iai_params;
	}
	
	public void setIai_params(Map<String, String> iai_params) {
		this.iai_params = iai_params;
	}
	
//	public void setIai_params(IaiParams iai_params) {
//	this.iai_params = iai_params;
//}

//	public IaiParams getIai_params() {
//		return iai_params;
//	}

//	public MultiValueMap<String, Object> getIai_params() {
//		return iai_params;
//	}

	// Setter Methods

	public void setSession_id(String session_id) {
		this.session_id = session_id;
	}

	public void setIai_datalake(String iai_datalake) {
		this.iai_datalake = iai_datalake;
	}

	public void setIai_datacipher(String iai_datacipher) {
		this.iai_datacipher = iai_datacipher;
	}

	public void setIai_datakey(String iai_datakey) {
		this.iai_datakey = iai_datakey;
	}

	public void setOn_finish_url(String on_finish_url) {
		this.on_finish_url = on_finish_url;
	}

	public List<String> getIai_files() {
		return iai_files;
	}

	public void setIai_files(List<String> iai_files) {
		this.iai_files = iai_files;
	}

	public List<IaiMetadata> getIai_dpo_metadata() {
		return iai_dpo_metadata;
	}

	public void setIai_dpo_metadata(List<IaiMetadata> iai_dpo_metadata) {
		this.iai_dpo_metadata = iai_dpo_metadata;
	}
}

//public class Iai_params {
//
//	// Getter Methods
//
//	// Setter Methods
//
//}
