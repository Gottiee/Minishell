<h1>Minishell</h1>


 - [ ] pipex(char **env, char *str)eliot
	<ul>
		<li>split les commandes par les pipes</li>
		<li>fork pour chaque </li>
		<li>split par les espaces</li>
		<li>parsing: '<<' / '<' / '>' / '>>' </li>
			- si < tcheck dabord le fd puis apres la commande
			- si << doc_here
			- apres avoir effectuer un << ou < regerder la sortie
			- si > crer le fichier / l'ouvrire et faire la commande ecraser les donner du fichier avec O_TRUNC
			- si >> // faire la commande et ecrire a la suite O_APPEND
			- <strong>ATTENTION</strong> si pipe apres > ou >> ne pas rediriger dans le pipe mets dans le fichier
	</ul>
- [X] int	cmd_type(char *arg); ->return 1 si execve et 0 une commande qu'on a codee. Theo
- [ ] promp theo 
	- [X] recuperer l'entree utilisateur et la clean
	- [X] l'envoyer au parsing
	- [ ] rajouter un historique des commandes pour pourvoir reprendre les commandes d'avant(fleche du haut)
- [ ] parsing: theo
	- [X]  si presence de \ ou de "' non fermer ou de ; marquer error syntax;
	- [ ] l'envoyer a pipex
	- [ ]  si un meta charcheter il doit etre afficher seulement s'il est dans des quotes (dans les double quote faut gerer les $ ` \$ \' \" \\ All other \ characters are literal (not special)) (dans les simple quotes tout les meta character sont desactiver / du coup il faut reactiver le $)(https://www.tutorialspoint.com/unix/unix-quoting-mechanisms.htm)
	<strong>ATTENTION</strong> si "" le dollar rester une variable
	- [ ]  si detection de =
		<ul>
			<li>verifier qu'il soit pas dans des quotes</li>
				- si l'est envoie a pipex sans les quotes
			<li>si l'est pas:</li>
				- regarder si l'argument passer avant est entre double quote si oui, envoyer a pipex sans les quotes.
				- verifier si apres le egal il y a un caratere autre que espace envoyer ce qu'il y apres les espaces a pipex
				- pas d'espace entre le nom de la variable et l'egal sinon pipex;
			<li>si tout vas bien</li>$
				- tchequer si la variable existe dans les variables d'environnement et la modifier si le cas present et ne pas la creer
					- sinon ajouter la variable dans une litse chaines de void etoiles; creer la stucture static et mettre
				- checker si la declaration de var est la derniere cmd de la ligne ("ok=5 | ls" >> ne fait pas la declaration de var // "ls | ok=5" fait la declaration de var mais pas le ls)
				<strong>ATTENTION</strong> stocker les chiffres dans un long long;
			</ul>
	- [ ]  creer une recherche par le nom pour trouver la structure dans la liste chainee (fonction dans les deux listes) :theo
	- [ ]  gerer pour le here 
- [ ] initialser liste chaine des variables d'env;
- [ ] gerer les signaux avec les controls.
- [ ] coder echo:
				- le tiret enleve le \n a la fin du echo
- [ ] coder cd:
- [ ] coder export and unset:
	- modifier la lister chainee 
	- modifier les variables d'environnement 
<strong>ATTENTION</strong> revoyer dans la variable global la valeur de sortie: int	return_value;
<strong>ATTENTION</strong> CREEER UN FREE ALL DANS LE MAIN POUR TJ FREE LES MALLOCS
- [ ]  historique
- [ ] makefile
- [ ] clean les .h

struct s_var_(local)/(env)
{
	s_var_? *next;
	char 	*var_name;
	void	*content;
}
