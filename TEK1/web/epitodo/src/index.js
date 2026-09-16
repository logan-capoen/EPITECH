require('dotenv').config();
const express = require('express');
const app = express();
const port = process.env.PORT;
const path = require('path');

const registerRouter = require('./routes/register');
const loginRouter = require('./routes/login');
const userApiRouter = require('./routes/user');
const usersRouter = require('./routes/users');
const todosRouter = require('./routes/todos');

app.use(express.json());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/register', registerRouter);
app.use('/login', loginRouter);
app.use('/user', userApiRouter);
app.use('/users', usersRouter);
app.use('/todos', todosRouter);

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
})

// Start the server
app.listen(port, () => {
    console.log(`Server is running on http://localhost:${port}`);
});
