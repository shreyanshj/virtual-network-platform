package virtual_network_manager_java;


public interface UserData<Type> {

	public abstract Type getData();
	public abstract void setData(Type data);
}
