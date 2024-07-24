const express = require('express');
const router = express.Router();
const conn = require('../Data/db');

// Rota POST para adicionar um novo produto
router.post('/cadastrar', (req, res) => {
  const { Nome_Produto, Descricao_Produto, Valor_Produto, Desconto_Produto, ID_Categoria } = req.body;

  const sql = 'INSERT INTO Produto (Nome_Produto, Descricao_Produto, Valor_Produto, Desconto_Produto, ID_Categoria) VALUES (?, ?, ?, ?, ?)';
  
  conn.query(sql, [Nome_Produto, Descricao_Produto, Valor_Produto, Desconto_Produto, ID_Categoria], (err, results) => {
    if (err) {
      console.log(err);
      return res.status(500).send("Erro ao inserir produto.");
    }

    res.status(201).send("Produto inserido com sucesso.");
  });
});

// Rota POST para atualizar um produto
router.post('/update', (req, res) => {
  const { ID_Produto, Nome_Produto, Descricao_Produto, Valor_Produto, Desconto_Produto, Disponivel } = req.body;

  const sql = 'UPDATE Produto SET Nome_Produto = ?, Descricao_Produto = ?, Valor_Produto = ?, Desconto_Produto = ?, Disponivel = ? WHERE ID_Produto = ?';
  
  conn.query(sql, [Nome_Produto, Descricao_Produto, Valor_Produto, Desconto_Produto, Disponivel, ID_Produto], (err, results) => {
    if (err) {
      console.log(err);
      return res.status(500).send("Erro ao atualizar produto.");
    }

    res.status(200).send("Produto atualizado com sucesso.");
  });
});

// Rota POST para deletar um produto
router.post('/delete', (req, res) => {
  const { ID_Produto } = req.body;

  const sql = 'DELETE FROM Produto WHERE ID_Produto = ?';
  
  conn.query(sql, [ID_Produto], (err, results) => {
    if (err) {
      console.log(err);
      return res.status(500).send("Erro ao deletar produto.");
    }

    res.status(200).send("Produto deletado com sucesso.");
  });
});

// Rota GET para acessar o cardápio
router.get('/cardapio', (req, res) => {
  const sql = `
    SELECT 
      Nome_Produto as Produto, 
      Descricao_Produto as Descricao, 
      (Valor_Produto - Desconto_Produto) as Subtotal
    FROM 
      Produto
    WHERE 
      Disponivel = 1
    GROUP BY 
      Nome_Produto, 
      Descricao_Produto`;

  conn.query(sql, (err, results) => {
    if (err) {
      console.log(err);
      return res.status(500).send("Erro ao acessar o cardápio.");
    }

    res.json(results);
  });
});

// Rota GET para filtrar produtos por categoria
router.get('/categoria/:ID_Categoria', (req, res) => {
  const { ID_Categoria } = req.params;

  const sql = `
    SELECT 
      Nome_Produto as Produto, 
      Descricao_Produto as Descricao, 
      (Valor_Produto - Desconto_Produto) as Subtotal
    FROM 
      Produto
    WHERE 
      Disponivel = 1 AND ID_Categoria = ?
    GROUP BY 
      Nome_Produto, 
      Descricao_Produto`;

  conn.query(sql, [ID_Categoria], (err, results) => {
    if (err) {
      console.log(err);
      return res.status(500).send("Erro ao filtrar produtos por categoria.");
    }

    res.json(results);
  });
});

// Rota GET para filtrar produtos por faixa de preço
router.get('/preco', (req, res) => {
  const { min, max } = req.query;

  const sql = `
    SELECT 
      Nome_Produto as Produto, 
      Descricao_Produto as Descricao, 
      (Valor_Produto - Desconto_Produto) as Subtotal
    FROM 
      Produto
    WHERE 
      Disponivel = 1 AND (Valor_Produto - Desconto_Produto) BETWEEN ? AND ?
    GROUP BY 
      Nome_Produto, 
      Descricao_Produto`;

  conn.query(sql, [min, max], (err, results) => {
    if (err) {
      console.log(err);
      return res.status(500).send("Erro ao filtrar produtos por faixa de preço.");
    }

    res.json(results);
  });
});


module.exports = router;
