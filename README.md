<h1>Minishell</h1>


- [ ] pipex(char **env, char *str) eliot
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
- [ ]int	cmd_type(char *arg); ->return 1 si execve et 0 une commande qu'on a codee. theo
- [ ]prompt: theo
- [ ]parsing:teho
	- [ ] verifier et supprimer les quotes.
	- [ ] si presence de \ ou de "' non fermer ou de ; marquer error syntax; 
	- [ ] si un meta charcheter il doit etre afficher seulement s'il est dans des quotes
	<strong>ATTENTION</strong> si "" le dollar rester une variable
	- [ ] si detection de =
		<ul>
			<li>verifier qu'il soit pas dans des quotes</li>
				- si l'est envoie a pipex
			<li>si l'est pas:</li>
				- regarder si l'argument passer avant est entre double quote si oui, envoyer a pipex sans les quotes.
				- verifier si apres le egal il y a un caratere autre que espace envoyer ce qu'il y apres les espaces a pipex
				- pas d'espace entre le nom de la variable et l'egal sinon pipex;
			<li>si tout vas bien</li>
				- tchequer si la variable existe dans les variables d'environnement et la modifier si le cas present et ne pas la creer
					- sinon ajouter la variable dans une litse chaines de void etoiles; creer la stucture static et mettre
				<strong>ATTENTION</strong> stocker les chiffres dans un long long;
		</ul>
	- [ ] creer une recherche par le nom pour trouver la structure dans la liste chainee (fonction dans les deux listes) theo
- [ ]initialser liste chaine des variables d'env;
- [ ]gerer les signaux avec les controls.
- [ ]coder echo:
	- le tiret enleve le \n a la fin du echo
- [ ]coder cd:
- [ ]coder export and unset:
	- modifier la lister chainee 
	- modifier les variables d'environnement 
<strong>ATTENTION</strong> revoyer dans la variable global la valeur de sortie: int	return_value;
<strong>ATTENTION</strong> CREEER UN FREE ALL DANS LE MAIN POUR TJ FREE LES MALLOCS
- [ ] historique

struct s_var_(local)/(env)
{
	s_var_? *next;
	char 	*var_name;
	void	*content;
}
