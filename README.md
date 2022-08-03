<h1>Minishell</h1>


eliot <button class="button">&timnes;</button>pipex(char **env, char *str)<br >
	<ul>
		<li>split les commandes par les pipes</li>
		<li>fork pour chaque </li>
		<li>split par les espaces</li>
		<li>parsing: '<<' / '<' / '>' / '>>' </li>
			- si < tcheck dabord le fd puis apres la commande<br>
			- si << doc_here<br>
			- apres avoir effectuer un << ou < regerder la sortie<br>
			- si > crer le fichier / l'ouvrire et faire la commande ecraser les donner du fichier avec O_TRUNC<br>
			- si >> // faire la commande et ecrire a la suite O_APPEND<br>
			- <h3>ATTENTION</h3> si pipe apres > ou >> ne pas rediriger dans le pipe mets dans le fichier<br>
	</ul>
	theo <button class="button"></button>int	cmd_type(char *arg); ->return 1 si execve et 0 une commande qu'on a codee.<br >
theo <button class="button"></button>prompt<br >
theo <button class="button"></button>parsing:<br >
		<button class="button"></button> verifier et supprimer les quotes.<br >
		<button class="button"></button> si presence de \ ou de "' non fermer ou de ; marquer error syntax; <br>
		<button class="button"></button> si un meta charcheter il doit etre afficher seulement s'il est dans des quotes<br >
		<h3>ATTENTION</h3> si "" le dollar rester une variable<br >
		<button class="button"></button> si detection de =<br >
			<ul>
				<li>verifier qu'il soit pas dans des quotes</li>
					- si l'est envoie a pipex<br >
				<li>si l'est pas:</li>
					- regarder si l'argument passer avant est entre double quote si oui, envoyer a pipex sans les quotes.<br >
					- verifier si apres le egal il y a un caratere autre que espace envoyer ce qu'il y apres les espaces a pipex<br >
					- pas d'espace entre le nom de la variable et l'egal sinon pipex;<br >
				<li>si tout vas bien</li>
					- tchequer si la variable existe dans les variables d'environnement et la modifier si le cas present et ne pas la creer
						- sinon ajouter la variable dans une litse chaines de void etoiles; creer la stucture static et mettre<br >
					<h3>ATTENTION</h3> stocker les chiffres dans un long long;<br >
			</ul>
		theo <button class="button"></button> creer une recherche par le nom pour trouver la structure dans la liste chainee (fonction dans les deux listes)<br >
? <button class="button"></button>initialser liste chaine des variables d'env;<br>
? <button class="button"></button>gerer les signaux avec les controls.<br>
? <button class="button"></button>coder echo:<br>
				- le tiret enleve le \n a la fin du echo<br>
? <button class="button"></button>coder cd:<br>
? <button class="button"></button>coder export and unset:<br>
	- modifier la lister chainee <br>
	- modifier les variables d'environnement <br>
<h3>ATTENTION</h3> revoyer dans la variable global la valeur de sortie: int	return_value;<br >
<h3>ATTENTION</h3> CREEER UN FREE ALL DANS LE MAIN POUR TJ FREE LES MALLOCS<br >
? <button class="button"></button> historique<br >

struct s_var_(local)/(env)<br>
{<br>
	s_var_? *next;<br>
	char 	*var_name;<br>
	void	*content;<br>
}<br>
