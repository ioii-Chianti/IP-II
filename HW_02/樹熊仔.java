import java.util.Scanner;
public class Main {
	 static int top = -1;
	 static int count = 0;
	 static boolean popflag = false;
	 
	 public static void push(char[] stack, char item){
	  top++;
	  stack[top] = item;
	  popflag = false;
	 }
	
	 public static void clean(char[] stack) {
		 for(int i = 0 ; i<stack.length ; i++)
			 stack[i] = 0;
		 top = -1;
	 }
	 
	 public static void pop(char[] stack){
	  top--;
	  count ++;
	  popflag = true;
	 }
	 
	 public static void main(String[] args) {
		 Scanner scn = new Scanner(System.in);
		 String text = scn.next();
		 
		 char[] arr = text.toCharArray();
		 char[] stack = new char[text.length()] ;
		 
		 push(stack, arr[0]);
		 push(stack, arr[1]);
		 
		 if(arr[0] == arr[1])
			 pop(stack);
		 
		 for(int i = 2 ; i < text.length() ; i++) {
			 
			 if(popflag == true) {
				 if(arr[i] == stack[top]) {
					 count++;
					 clean(stack);
					 popflag = false;
					 continue;
				 }
				 else {
					 clean(stack);
					 push(stack, arr[i]);
					 continue;
				 }
			 }
			 
			 push(stack, arr[i]);
			 
			 if(top == 0)
				 continue;
			 else if(top == 1) {
				 if(stack[top] == stack[top-1])
					 pop(stack);
			 }
			 else {
				 if(stack[top] == stack[top-1] || stack[top] == stack[top-2]) {
					 pop(stack);
				 }
			 }
				 
		 }
		 System.out.println(count);
	}
}
