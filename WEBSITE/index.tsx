import React from 'react';
import ReactDOM from 'react-dom/client';
import App from './App';
import { API_URL } from './config';

const nativeFetch = window.fetch.bind(window);
const apiBase = new URL(API_URL, window.location.href);

window.fetch = (input: RequestInfo | URL, init: RequestInit = {}) => {
  const requestUrl = new URL(
    typeof input === 'string' || input instanceof URL ? input.toString() : input.url,
    window.location.href
  );
  const targetsApi = requestUrl.origin === apiBase.origin &&
    (requestUrl.pathname === apiBase.pathname || requestUrl.pathname.startsWith(`${apiBase.pathname}/`));

  return nativeFetch(input, targetsApi ? { ...init, credentials: init.credentials ?? 'include' } : init);
};

const rootElement = document.getElementById('root');
if (!rootElement) {
  throw new Error("Could not find root element to mount to");
}

const root = ReactDOM.createRoot(rootElement);
root.render(
  <React.StrictMode>
    <App />
  </React.StrictMode>
);
