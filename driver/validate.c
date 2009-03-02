 /*!  *	validate a password for a user   */    /*  * Includes   */  #include <stdio.h> #include <ctype.h> #include "pwd.h"     /*  *)  *	Validate a VMS UserName/Password pair.   *  */     int validate_user(name,password) char *name;  char *password;  {  	char password_buf[64];  	char username_buf[31];  	char encrypt_buf[8];  	register int i; 	register char *cp,*cp1; 	struct passwd *user_entry;    	/*  	 *	Get the users UAF entry  	 */ 	user_entry = getpwnam(name);    	/* 1 	 *	If user_entry == NULL then we got a bad error % 	 *	return -1 to indicate a bad error  	 */% 	if (user_entry == NULL) return (-1);    	/*  	 *	Uppercase the password 	 */ 	cp = password;  	cp1 = password_buf; 	while (*cp) 	   if (islower(*cp))  		*cp1++ = toupper(*cp++); 	   else 		*cp1++ = *cp++;  	/* " 	 *	Get the length of the password 	 */ 	i = strlen(password); 	/*  	 *	Encrypt the password 	 */B 	hash_vms_password(encrypt_buf,password_buf,i,user_entry->pw_name,2 			  user_entry->pw_encrypt, user_entry->pw_salt);4 	if (bcmp(encrypt_buf,user_entry->pw_passwd,8) == 0) 		return(1); 	else	return(0); }   