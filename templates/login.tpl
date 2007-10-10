<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<link rel="stylesheet" href="{$css}" type="text/css" />
<!-- shortcut icon that displays on the browser window -->
<link rel="shortcut icon" href="images/mni_icon.ico" type="image/ico" />
<!-- page title -->
<title>{$title}</title>
</head>

<body>

<form action="{$action}" method="post">

<table align="center" bgcolor="#D3DCE3" border="0" cellpadding="2" cellspacing="0">
    <tr>
    	<th align="left" class="banner" colspan="2" background="images/title_background.jpg">
    	    Autism Centers of Excellence (ACE) - Baby Sibs Network
	    </th>
</tr>
    	<td><img src="images/mni_logo_transparent.gif" alt="Montreal Neurological Institute" border="0" width="128" height="106" /></td>
	    <td>
	        <table border="0" cellpadding="2" cellspacing="2">
<br>
        <tr>Montreal Neurological Hospital and Institute</tr>	
		<tr>
		            <td align="center" colspan="2">{$error_message}&nbsp;</td>
    		    </tr>
        		<tr>
	        	    <th align="right">User:</th>
		            <td align="left"><input name="username" size="40" tabindex="1" type="text" value="{$username}" /></td>
		            <td align="center" rowspan="2" valign="center"><input class="button" name="login" type="submit" value="login" /></td>
        		</tr>
	        	<tr>
		            <th align="right">Password:</th>
		            <td align="left"><input name="password" size="40" tabindex="2" type="password" /></td>
        		</tr>
                <tr>
	                <td align="center" colspan="2"><a href="lost_password.php">Forgot your password?</a></td>
	            </tr>
   	        </table>
    	</td>
    </tr>
    <tr>
    	<td align="left" class="tabox" colspan="2">
    	    Created By: <a href="http:www.bic.mni.mcgill.ca" target="_blank">McConnell Brain Imaging Centre</a>
	    </td>
    </tr>
</table>

</form>

</body>
</html>
