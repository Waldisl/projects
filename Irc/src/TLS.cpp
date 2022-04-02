
# include "Server.hpp"

SSL_CTX	*Server::InitCTX(void)
{
	const SSL_METHOD *method;
	SSL_CTX *ctx;

	OpenSSL_add_all_algorithms();
	SSL_load_error_strings();
	method = SSLv23_server_method();
	ctx = SSL_CTX_new(method);
	if ( ctx == NULL ) {
		ERR_print_errors_fp(stderr);
		std::cerr << "in InitCTX() error" << std::endl;
	}
	return ctx;
}

void Server::LoadCertificates(SSL_CTX* ctx, char* CertFile, char* KeyFile, bool serv)
{
	if (serv) {

		if (SSL_CTX_load_verify_locations(ctx, CertFile, KeyFile) != 1)
			ERR_print_errors_fp(stderr);

		if (SSL_CTX_set_default_verify_paths(ctx) != 1)
			ERR_print_errors_fp(stderr);

	}

	if (SSL_CTX_use_certificate_file(ctx, CertFile, SSL_FILETYPE_PEM) <= 0)
	{
		ERR_print_errors_fp(stderr);
		abort();
	}

	if (SSL_CTX_use_PrivateKey_file(ctx, KeyFile, SSL_FILETYPE_PEM) <= 0)
	{
		ERR_print_errors_fp(stderr);
		abort();
	}

	if (!SSL_CTX_check_private_key(ctx))
	{
		fprintf(stderr, "Private key does not match the public certificate\n");
		abort();
	}

}
