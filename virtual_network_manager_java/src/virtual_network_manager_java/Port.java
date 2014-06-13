package virtual_network_manager_java;

public class Port {
	private int no;
	private String name;

	public Port(int no, String name){
		this.no = no;
		this.name = name;
	}
	
	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getNo() {
		return no;
	}

	public void setNo(int no) {
		this.no = no;
	}
	
}
