package fr.cea.bigpi.fhe.dap.patternsearch.model.analyticRequestPayload;

import org.springframework.validation.annotation.Validated;

import com.fasterxml.jackson.annotation.JsonProperty;


@Validated
public class IaiMetadata {
	@JsonProperty("id")
	private String id;
	@JsonProperty("dsa_id")
	private String dsa_id;
	@JsonProperty("start_time")
	private String start_time;
	@JsonProperty("end_time")
	private String end_time;
	@JsonProperty("event_type")
	private String event_type;
	@JsonProperty("organization")
	private String organization;
	@JsonProperty("file_extension")
	private String file_extension;

	// Getter Methods

	public String getId() {
		return id;
	}

	public String getDsa_id() {
		return dsa_id;
	}

	public String getStart_time() {
		return start_time;
	}

	public String getEnd_time() {
		return end_time;
	}

	public String getEvent_type() {
		return event_type;
	}

	public String getOrganization() {
		return organization;
	}

	public String getFile_extension() {
		return file_extension;
	}

	// Setter Methods

	public void setId(String id) {
		this.id = id;
	}

	public void setDsa_id(String dsa_id) {
		this.dsa_id = dsa_id;
	}

	public void setStart_time(String start_time) {
		this.start_time = start_time;
	}

	public void setEnd_time(String end_time) {
		this.end_time = end_time;
	}

	public void setEvent_type(String event_type) {
		this.event_type = event_type;
	}

	public void setOrganization(String organization) {
		this.organization = organization;
	}

	public void setFile_extension(String file_extension) {
		this.file_extension = file_extension;
	}
}
