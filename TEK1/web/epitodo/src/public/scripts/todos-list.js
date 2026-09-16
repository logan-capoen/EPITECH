(async () => {
    try {
      const response = await fetch('/todos', {
        method: 'GET',
        headers: {
          'Content-Type': 'application/json',
        },
      });
  
      if (response.ok) {
        const data = await response.json();
        const todos = data;
        const main = document.querySelector('main');
  
        // Create a table
        const table = document.createElement('table');
        table.border = '1';
        table.style.margin = '20px auto';
        table.style.borderCollapse = 'collapse';
  
        // Create table header
        const thead = document.createElement('thead');
        const headerRow = document.createElement('tr');
        const headers = ['Done', 'ID', 'Title', 'Description', 'User ID', 'Due Time', 'Status'];
        headers.forEach(text => {
          const th = document.createElement('th');
          th.textContent = text;
          th.style.padding = '8px';
          th.style.backgroundColor = '#35424a';
          th.style.color = '#fff';
          headerRow.appendChild(th);
        });
        thead.appendChild(headerRow);
        table.appendChild(thead);
  
        // Create table body with each todo
        const tbody = document.createElement('tbody');
        todos.forEach(todo => {
          const row = document.createElement('tr');
  
          // Checkbox column for completed status
          const checkboxCell = document.createElement('td');
          const checkbox = document.createElement('input');
          checkbox.type = 'checkbox';
          checkbox.checked = todo.completed || false;
          checkboxCell.style.textAlign = 'center';
          checkboxCell.style.padding = '8px';
          checkboxCell.appendChild(checkbox);
          row.appendChild(checkboxCell);
  
          // ID
          const idCell = document.createElement('td');
          idCell.textContent = todo.id;
          idCell.style.padding = '8px';
          row.appendChild(idCell);
  
          // Title
          const titleCell = document.createElement('td');
          titleCell.textContent = todo.title;
          titleCell.style.padding = '8px';
          row.appendChild(titleCell);
  
          // Description
          const descCell = document.createElement('td');
          descCell.textContent = todo.description || '';
          descCell.style.padding = '8px';
          row.appendChild(descCell);
  
          // User ID
          const userCell = document.createElement('td');
          userCell.textContent = todo.user_id || '';
          userCell.style.padding = '8px';
          row.appendChild(userCell);
  
          // Due Time
          const dueCell = document.createElement('td');
          dueCell.textContent = todo.due_time || '';
          dueCell.style.padding = '8px';
          row.appendChild(dueCell);
  
          // Status
          const statusCell = document.createElement('td');
          statusCell.textContent = todo.status || (todo.completed ? 'Completed' : 'Pending');
          statusCell.style.padding = '8px';
          row.appendChild(statusCell);
  
          tbody.appendChild(row);
        });
        table.appendChild(tbody);
        main.appendChild(table);
      } else {
        console.error('Failed to fetch todos');
      }
    } catch (err) {
      console.error('Error:', err);
    }
  })();
