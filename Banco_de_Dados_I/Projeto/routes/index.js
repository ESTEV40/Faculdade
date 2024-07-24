const express = require('express');
const router = express.Router();

// Rota para a página inicial
router.get('/', (req, res) => {
  res.render('index');
});

// Rota para a página de login do funcionário
router.get('/login_funcionario', (req, res) => {
  res.render('login_funcionario');
});

// Rota para a página de cadastro do cliente
router.get('/cadastro_cliente', (req, res) => {
  res.render('cadastro_cliente');
});

// Rota para a dashboard do cliente
router.get('/dashboard_cliente', (req, res) => {
  res.render('dashboard_cliente');
});

// Rota para a dashboard do funcionário
router.get('/dashboard_funcionario', (req, res) => {
  res.render('dashboard_funcionario');
});

// Rota para a página de fazer pedido
router.get('/fazer_pedido', (req, res) => {
  res.render('fazer_pedido');
});

// Rota para a página de acompanhar pedidos
router.get('/acompanhar_pedidos', (req, res) => {
  res.render('acompanhar_pedidos');
});

// Rotas para páginas de gerenciamento de produtos e categorias
router.get('/inserir_produto', (req, res) => {
  res.render('inserir_produto');
});

router.get('/alterar_produto', (req, res) => {
  res.render('alterar_produto');
});

router.get('/deletar_produto', (req, res) => {
  res.render('deletar_produto');
});

router.get('/inserir_categoria', (req, res) => {
  res.render('inserir_categoria');
});

router.get('/deletar_categoria', (req, res) => {
  res.render('deletar_categoria');
});

router.get('/alterar_mesa', (req, res) => {
  res.render('alterar_mesa');
});

module.exports = router;
